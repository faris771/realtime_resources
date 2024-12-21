#include <pthread.h> 

pthread_mutexattr_t mattr;
pthread_mutex_t *mptr;
int ret; 

ret = pthread_mutexattr_init(&mattr); 

/* resetting to its default value: private */
ret = pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_PRIVATE);

pthread_mutex_init(mptr, &mattr);
