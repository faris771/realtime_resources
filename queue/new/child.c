#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>

struct mesg_buffer {
  long mesg_type;
  char mesg_text[100];
} message;

int main(int argc, char *argv[]) {
  key_t key;
  int msgid, i;
  long type;
  
  if ( argc < 4 ) {
    printf("Insufficient arguments!\n");
    exit(-1);
  }

  key  = atoi(argv[1]);
  i    = atoi(argv[2]);
  type = atol(argv[3]);

  printf("Child => key = %d\n", key);
  
  if ( (msgid = msgget(key, 0 )) == -1 ) {
    printf("Unable to connect to message queue");
    exit(-2);
  }
  
  msgrcv(msgid, &message, sizeof(message), type, 0);
  printf("Data Received for child %d: %s\n", i, message.mesg_text);

  return 0;
}
