#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define LENGTH_OF_LINE 1024

struct msgbuf {
   long mType;
   char mText[LENGTH_OF_LINE];
};

int main() {
   int qId;
   key_t key;
   struct msgbuf msg_from, msg_to;
   key = ftok( "/tmp", 'A' );
   qId = msgget( key, IPC_CREAT | 0666 );
   msgrcv( qId, &msg_from, sizeof msg_from.mText, 1, 0 );
   printf( "Message from server = %s\n", msg_from.mText );
   msg_to.mType = 2;
   strncpy(msg_to.mText, "Hi Server, It's CLIENT",22);
   msgsnd( qId, &msg_to, sizeof(msg_to.mText), 0 );
   return 0;
}