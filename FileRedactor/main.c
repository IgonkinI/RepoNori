#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include "string.h"

#define MAX_NAME_LEN 20
#define buffer 100
void sig_winch(int signo) {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
  resizeterm(size.ws_row, size.ws_col);
}

int main(int argc, char **argv) {
  char name[MAX_NAME_LEN + 1];
  initscr();
  mousemask(BUTTON1_CLICKED, NULL);
  keypad(stdscr, TRUE);
  signal(SIGWINCH, sig_winch);
  curs_set(TRUE);
  start_color();
  refresh();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  wbkgd(stdscr, COLOR_PAIR(1));
  wattron(stdscr, A_BOLD);
  wprintw(stdscr, "\n\t\tApocalipse Text Editor\n");
  wprintw(stdscr, "\nEnter the FileName:\n");
  wgetnstr(stdscr, name, MAX_NAME_LEN);
  name[MAX_NAME_LEN - 1] = 0;

  FILE *fp;
  fp = fopen(name, "a+r");

  char writed[buffer];
  int y = 0;
  int x = 0;

  clear();
  refresh();
  while (fgets(writed, sizeof(writed), fp)) {
    writed[(sizeof(writed)/sizeof(char))-1] = '\0';
       // writed[(sizeof(writed)/sizeof(char))-2] = '\0';
    mvwaddstr(stdscr, x, y, writed);
    x++;
    
     
    x++;
  }
  fclose(fp);
 // x=0;
  //y=0;
  int max_Line = x;
  chtype *buff;
  char to_file;
  move(0, 0);
  do {
    int symb_int =  getch();
    switch (symb_int) {
      case KEY_F(2):
        fp = fopen(name, "w");
        
        
        for (int i = 0; i <= max_Line + 1; i++) {
          
          buff = calloc(buffer, sizeof(chtype));	
          mvwinchnstr(stdscr, i, 0, buff, buffer);
          for (int j = 0; j <= buffer; j++) {
            to_file = (char)buff[j];
            fputc(to_file, fp);
          }
          fputs("\n",fp);
          free(buff);
          
        }

        clear();
        fclose(fp);
        curs_set(FALSE);
        move(buffer + 1, buffer + 1);
        wprintw(stdscr, "\nPress any key to continue...");
        refresh();
        getch();
        endwin();
        exit(EXIT_SUCCESS);
        break;

      case KEY_UP:
        if (x > 1) {
      x--;
          move(x, y);
        }
        refresh();
        break;

      case KEY_DOWN:
        x++;
        y = 0;
        move(x, y);
        break;

      case KEY_LEFT:
        if (y > 0) {
          y--;
          move(x, y);
        }
        break;

      case KEY_RIGHT:
        y++;
        move(x, y);
        break;

      case 8:
        if (y > 0) {
          y--;
          move(x, y);
        }

      case 10:
        x++;
        y = 0;
        move(x, y);
        break;

      default:

      //  y++;

        if (x > max_Line) {
          max_Line = x;
        }

        break;
    }

  } while (TRUE);

  curs_set(FALSE);
  move(31, 1);
  printw("Press any key to continue...");
  refresh();
  getch();
  endwin();
  exit(EXIT_SUCCESS);
}