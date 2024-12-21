#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
//#include "queue.h"

typedef struct mesg_buffer {
  long mesg_type;
  char mesg_text[100];
} message;

void report_and_exit(const char* msg) {
  perror(msg);
  exit(-1); /* EXIT_FAILURE */
}

int main() {
  message msg;
  
  key_t key = ftok(".", 'S');
  
  if (key < 0)
    report_and_exit("couldn't get key...");
  
  int qid = msgget(key, 0666 | IPC_CREAT);
  if (qid < 0)
    report_and_exit("couldn't get queue id...");
  
  char* payloads[] = {"msg1", "msg2", "msg3", "msg4", "msg5", "msg6"};
  long types[] = {1, 1, 2, 2, 3, 3}; /* each must be > 0 */

  
  for (int i = 0; i < 6; i++) {
    msg.mesg_type = types[i];
    strcpy(msg.mesg_text, payloads[i]);
    
    msgsnd(qid, &msg, sizeof(msg), IPC_NOWAIT); /* don't block */
    printf("%s sent as type %i\n", msg.mesg_text, (int) msg.mesg_type);
  }
  
  return 0;
}
