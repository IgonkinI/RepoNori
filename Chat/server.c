#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH_OF_LINE 128
#define LENGTH_NAME 32
#define MAX_SIZE_OF_HISTORY_DUMP 2048
#define MAX_NUMBER_IN_CHAT 100
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

int main() {
  int qId;
  key_t key_to_connect;
  int current_num_of_client = 0;
  struct connect msg_from[MAX_NUMBER_IN_CHAT];
  struct store_of_message store[MAX_NUMBER_IN_CHAT];
  int curr_pos_in_chat = 0;
  key_to_connect = ftok("/tmp", 'A');
  qId = msgget(key_to_connect, IPC_CREAT | 0666);
  int curr_pos = 0;
  // По второму приоритету вытаскиваем из очереди подключение NAME, PID
  // Потом вытаскиваем из очереди и печатаем сообщения приоритет которых узанли
  // заранее.
  char connect_mes[] = " Joined the chat! Welcome! \n";
  do {
    // Подключение клиента к серверу

    if (0 < msgrcv(qId, &msg_from[current_num_of_client],
                   sizeof(struct connect) - sizeof(long), 2, IPC_NOWAIT)) {
      int i = 0;
      while (msg_from[current_num_of_client].mText_Name[i] != '\n') {
        i++;
      }

      msg_from[current_num_of_client].mText_Name[i] = '\0';
      printf("\n%s Joined the chat! Welcome! \n",
             msg_from[current_num_of_client].mText_Name);

      strcpy(store[curr_pos_in_chat].history_of_messages,
             msg_from[current_num_of_client].mText_Name);

      for (i = 0; i < strlen(connect_mes); i++) {
        store[curr_pos_in_chat].history_of_messages
            [i + strlen(msg_from[current_num_of_client].mText_Name)] =
            connect_mes[i];
      }
      curr_pos_in_chat++;

      for (i = 0; i < curr_pos_in_chat; i++) {
        store[i].mType = (long)msg_from[current_num_of_client].this_pid;

        store[i].to_stop = 0;

        msgsnd(qId, &store[i], sizeof(struct store_of_message) - sizeof(long),
               0);
      }

      store[i].mType = (long)msg_from[current_num_of_client].this_pid;
      store[i].to_stop = 1;
      msgsnd(qId, &store[i], sizeof(struct store_of_message) - sizeof(long), 0);
      current_num_of_client++;
    }

    // Отображение сообщений на сервере и сохранение дампа
    // for (int curr_pos = 0; curr_pos < current_num_of_client; curr_pos++){

    struct message mes;

    if (0 < msgrcv(qId, &mes, sizeof(struct message) - sizeof(long), 1,
                   IPC_NOWAIT)) {
      printf("\n%s>>%s", mes.mText_Name, mes.mText);
      // Создаем сохранение сообщений в переменную store
      int i = 0;

      for (i = 0; i < strlen(msg_from[curr_pos].mText_Name); i++) {
        store[curr_pos_in_chat].history_of_messages[i] = mes.mText_Name[i];
      }
      store[curr_pos_in_chat].history_of_messages[i] = '>';
      i++;
      store[curr_pos_in_chat].history_of_messages[i] = '>';
      i++;
      for (int j = 0; j < strlen(mes.mText); j++) {
        store[curr_pos_in_chat].history_of_messages[i + j] = mes.mText[j];
      }

      // Отправляем полученное сообщение всем участникам
      for (i = 0; i <= current_num_of_client; i++) {
        mes.mType = 10;
        msgsnd(qId, &mes, sizeof(struct message) - sizeof(long), 0);
      }
      curr_pos_in_chat++;
    }

    sleep(0.1);

  } while (1);

  return 0;
}