#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH_OF_LINE 1024
struct msgbuf {
   long mType;
   char mText[LENGTH_OF_LINE];
};

int main() {
   int qId;
   key_t key;
   struct msgbuf msg_to, msg_from;
   key = ftok( "/tmp", 'A' );
   qId = msgget( key, IPC_CREAT | 0666 ); 
   strcpy( msg_to.mText, "Hello from Server" );
   msg_to.mType = 1;
   msgsnd( qId, &msg_to, sizeof(msg_to.mText), 0 );
   msgrcv( qId, &msg_from, sizeof(msg_from.mText), 2, 0 );
   printf("\nMessage from client = %s\n", msg_from.mText);
  return 0;
}