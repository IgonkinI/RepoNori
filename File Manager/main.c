#include <curses.h>
#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include "string.h"

void init_wins(WINDOW **wins, int n);
void sig_winch(int signo) {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
  resizeterm(size.ws_row, size.ws_col);
}

void print_DIR(WINDOW *win, int y, int x, int half_n_cols, char *road) {
  wclear(win);
  box(win, 0, 0);
  y = 2;
  x = 1;

  mvwaddstr(win, 1, (half_n_cols / 2), "WINDOW");
  wrefresh(win);

  DIR *dir;
  struct dirent *entry;

  dir = opendir(road);
  if (!dir) {
    perror("diropen");
    exit(1);
  };

  while ((entry = readdir(dir)) != NULL) {
    char *ptr = calloc(strlen(entry->d_name) + 1, sizeof(char));
    strncpy(ptr, entry->d_name, strlen(entry->d_name));
    ptr[strlen(ptr)] = ' ';
    mvwaddstr(win, y, x, ptr);
    free(ptr);
    y++;
  };
  y = 2;
  x = 1;
  wmove(win, y, x);
  closedir(dir);
  wrefresh(win);
}

int main(int argc, char const *argv[]) {
  initscr();
  mousemask(BUTTON1_CLICKED, NULL);

  signal(SIGWINCH, sig_winch);
  curs_set(TRUE);

  int main_n_cols = getmaxx(stdscr);
  int main_n_line = getmaxy(stdscr);
  // printw("\nX = %d\nY = %d\n",main_n_cols, main_n_line );
  int half_n_cols = main_n_cols / 2;
  int half_n_line = main_n_line;
  int begin_y = 0;
  int begin_x = 0;

  WINDOW *left_win = newwin(half_n_line, half_n_cols, begin_y, begin_x);
  box(left_win, 0, 0);
  mvwaddstr(left_win, 1, (half_n_cols / 2), "Left Table");
  wrefresh(left_win);

  WINDOW *right_win = newwin(half_n_line, half_n_cols, begin_y, half_n_cols);
  box(right_win, 0, 0);
  mvwaddstr(right_win, 1, (half_n_cols / 2), "Right Table");

  wrefresh(right_win);

  int sym;
  int y = 2;
  int x = 1;

  int curr_win = 0;
  wmove(left_win, y, x);
  char *road1;
  char *road2;
  road1 = calloc(1024, sizeof(char));
  road2 = calloc(1024, sizeof(char));
  road1[0] = '/';
  road2[0] = '/';
  char *buff;
  char *buff1;
  // buff = calloc(20,sizeof(char));
  int mid = 0;
  int mid1 = 0;
  char mid_sym;
  int pos = 1;
  int pos1 = 1;
  int tr = 1;
  while (tr == 1) {
    keypad(left_win, TRUE);
    keypad(right_win, TRUE);

    switch (curr_win) {
        // Левое окно
      case 0:

        switch (sym = wgetch(left_win)) {
          case KEY_UP:

            if (y > 2) {
              y--;
              wmove(left_win, y, x);
              wrefresh(left_win);
            } else {
              wmove(left_win, y, x);
              wrefresh(left_win);
            }
            break;

          case KEY_DOWN:
            y++;
            wmove(left_win, y, x);
            wrefresh(left_win);
            break;

          case KEY_LEFT:
            wmove(left_win, y, x);
            wrefresh(left_win);
            break;

          case KEY_RIGHT:
            curr_win = 1;
            break;

          case KEY_F(1):
            print_DIR(left_win, y, x, half_n_cols, road1);
            y = 2;
            x = 1;
            wmove(left_win, y, x);
            wrefresh(left_win);
            break;

          case KEY_F(2):

            buff = (char *)calloc(half_n_cols, sizeof(char));

            for (int i = 0; i < half_n_cols; i++) {
              buff[i] = ' ';
            }

            mvwinstr(left_win, y, x, buff);

            mid = 0;

            while (((buff[mid] >= 46) && (buff[mid] <= 57)) ||
                   ((buff[mid] >= 65) && (buff[mid] <= 90)) ||
                   ((buff[mid] >= 97) && (buff[mid] <= 122))) {
              road1[pos] = buff[mid];
              pos++;
              mid++;
            }
            road1[pos] = '/';
            pos++;
            mid = 0;

            print_DIR(left_win, y, x, half_n_cols, road1);
            wrefresh(left_win);
            free(buff);
            y = 2;
            x = 1;

            wmove(left_win, y, x);
            break;

          case KEY_F(3):
            tr = 0;
            break;

          default:
            break;
        }

        break;

        // Правое окно
      case 1:

        switch (sym = wgetch(right_win)) {
          case KEY_UP:

            if (y > 2) {
              y--;
              wmove(right_win, y, x);
              wrefresh(right_win);
            } else {
              wmove(right_win, y, x);
              wrefresh(right_win);
            }
            break;

          case KEY_DOWN:
            y++;
            wmove(right_win, y, x);
            wrefresh(right_win);
            break;

          case KEY_LEFT:
            curr_win = 0;
            break;

          case KEY_RIGHT:
            wmove(right_win, y, x);
            wrefresh(right_win);
            break;

          case KEY_F(1):
            print_DIR(right_win, y, x, half_n_cols, road2);
            break;

          case KEY_F(2):

            buff1 = (char *)calloc(half_n_cols, sizeof(char));

            for (int i = 0; i < half_n_cols; i++) {
              buff1[i] = ' ';
            }

            mvwinstr(right_win, y, x, buff1);

            mid1 = 0;

            while (((buff1[mid1] >= 46) && (buff1[mid1] <= 57)) ||
                   ((buff1[mid1] >= 65) && (buff1[mid1] <= 90)) ||
                   ((buff1[mid1] >= 97) && (buff1[mid1] <= 122))) {
              road2[pos1] = buff1[mid1];
              pos1++;
              mid1++;
            }
            road2[pos1] = '/';
            pos1++;
            mid1 = 0;

            print_DIR(right_win, y, x, half_n_cols, road2);
            wrefresh(right_win);
            free(buff1);
            y = 2;
            x = 1;

            wmove(right_win, y, x);
            break;

          case KEY_F(3):
            tr = 0;
            break;

          default:
            break;
        }

        break;

      default:
        break;
    }
  }

  // wgetch(stdscr);
  // wgetch(right_win);

  // getch();

  delwin(left_win);
  delwin(right_win);
  free(road1);
  free(road2);
  // free(buff);
  endwin();
  return 0;
}