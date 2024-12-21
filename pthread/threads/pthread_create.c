#include <stdio.h>       /* standard I/O routines                 */
#include <unistd.h>
#include <pthread.h>     /* pthread functions and data structures */


/* function to be executed by the new thread */
void*
do_loop(void* data)
{
  int i;			/* counter, to print numbers */
  int j;			/* counter, for delay        */
  int me = *((int*)data);     /* thread identifying number */

  //while ( 1 ) {
  for (i=0; i<10; i++) {
    
    //if ( me != 3 )
      for (j=0; j<50000; j++); /* delay loop */
    //sleep(1);
    printf("'%d' - Got '%d'\n", me, i);
    fflush(stdout);
  }
  
  /* exit the thread */
  if (me != 3) {
    pthread_exit((void *) -3);
  }
  //}
}

/* like any C program, program's execution begins in main */
int
main(int argc, char* argv[])
{
  int        thr_id;         /* thread ID for the newly created thread */
  int        thr_id1;         /* thread ID for the newly created thread */
  pthread_t  p_thread, p_thread1;       /* thread's structure                     */
  int        a         = 1;  /* thread 1 identifying number            */
  int        b         = 2;  /* thread 2 identifying number            */
  int        c         = 3;  /* thread 2 identifying number            */
  int        status, status1;
  
  /* create a new thread that will execute 'do_loop()' */
  thr_id = pthread_create(&p_thread, NULL, do_loop, (void*)&a);
  thr_id1 = pthread_create(&p_thread1, NULL, do_loop, (void*)&b);

  do_loop(&c);

  pthread_join(p_thread, (void *) &status);
  pthread_join(p_thread1, (void *) &status1);  

  //pthread_join(p_thread, NULL);  

  printf("thread ended with status %d\n", status);
  fflush(stdout);
  printf("thread ended with status %d\n", status1);
  fflush(stdout);
  
  /* NOT REACHED */
  return 0;
}
