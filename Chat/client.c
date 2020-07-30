#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <curses.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>

#define LENGTH_OF_LINE 128
#define LENGTH_NAME 32
#define MAX_SIZE_OF_HISTORY_DUMP 2048
pthread_mutex_t mutex;

void init_wins(WINDOW **wins, int n);
void sig_winch(int signo) {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
  resizeterm(size.ws_row, size.ws_col);
}

struct connect {
  long mType;
  char mText_Name[LENGTH_NAME];
  char mText[LENGTH_OF_LINE];
  pid_t this_pid;
};

struct message {
  long mType;
  char mText[LENGTH_OF_LINE];
  char mText_Name[LENGTH_NAME];
  pid_t pd;
};

struct store_of_message {
  long mType;
  char history_of_messages[MAX_SIZE_OF_HISTORY_DUMP];
  int to_stop;
};
// Обновление чата выведен в отдельный поток

void *print_mes() {
  int qId;
  key_t key_to_connect;
  key_to_connect = ftok("/tmp", 'A');
  qId = msgget(key_to_connect, IPC_CREAT | 0666);

  while (1) {
    struct message mes_from;
    // Сервер отправляет сообщение, отправленное другим клентом, с приоритетом
    // 10.
    if (0 < msgrcv(qId, &mes_from, sizeof(struct message) - sizeof(long), 10,
                   IPC_NOWAIT)) {
      if (mes_from.pd != getpid()) {
        pthread_mutex_lock(&mutex);
        printw(mes_from.mText_Name);
        printw(">>");
        printw(mes_from.mText);
        refresh();
        printw("\n");
        pthread_mutex_unlock(&mutex);
      }
    }

    sleep(0.2);
  }
  return 0;
}

int main() {
  pthread_mutex_init(&mutex, NULL);
  initscr();
  signal(SIGWINCH, sig_winch);
  curs_set(TRUE);

  int qId;
  key_t key_to_connect;
  struct connect msg_to;
  char test_message[] = "Try to connect server!";
  // Получаем доступ к очереди, по приоритету 2 передаются данные для
  // подключения PID, NAME.
  key_to_connect = ftok("/tmp", 'A');
  qId = msgget(key_to_connect, IPC_CREAT | 0666);

  // При подключениив  очередь приходят сообщения с приоритетом 2.
  msg_to.mType = 2;
  printw("Enter name:", stdout);
  wgetstr(stdscr, msg_to.mText_Name);  //, LENGTH_NAME, stdin);
  wrefresh(stdscr);
  strncpy(msg_to.mText, test_message, strlen(test_message));
  msg_to.this_pid = getpid();
  msgsnd(qId, &msg_to, sizeof(struct connect) - sizeof(long), 0);

  pid_t mypid = getpid();
  long typeM = (long)mypid;
  do {
    struct store_of_message store;

    if (0 < msgrcv(qId, &store, sizeof(struct store_of_message) - sizeof(long),
                   typeM, IPC_NOWAIT)) {
      if (store.to_stop == 1) {
        break;
      }
      wprintw(stdscr, "\n");
      wrefresh(stdscr);
      wprintw(stdscr, store.history_of_messages);
      wrefresh(stdscr);
    }

  } while (1);

  pthread_t pthread_ID;
  pthread_create(&pthread_ID, NULL, print_mes, NULL);

  do {
    // Все сообщения в чат уходят с приоритетом 1. Сервер их отправляет ровно
    // столько раз, сколько клиентов в чате.
    struct message mes;
    mes.pd = mypid;
    getstr(mes.mText);  //, LENGTH_OF_LINE, stdin);
    strcpy(mes.mText_Name, msg_to.mText_Name);
    wrefresh(stdscr);
    if (!strncmp(mes.mText, "quit", 4)) {
      endwin();
      break;
    }

    mes.mType = 1;
    msgsnd(qId, &mes, sizeof(struct message) - sizeof(long), 0);
    sleep(0.1);

  } while (1);

  return 0;
}