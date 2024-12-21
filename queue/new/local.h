#ifndef __LOCAL_H_
#define __LOCAL_H_

typedef struct mesg_buffer {
  long mesg_type;
  char mesg_text[100];
} message;

#endif
