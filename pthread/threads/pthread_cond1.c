#include <stdio.h>
#include <unistd.h>  
#include <pthread.h>  

#define TCOUNT 50  
#define WATCH_COUNT 30  

int count = 0;  
int flag = 0;

void inc_count(int *);  
void watch_count(int *);  

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;  
pthread_cond_t count_threshold_cv = PTHREAD_COND_INITIALIZER;  
 
int  thread_ids[3] = {0,1,2};  
int r = 0;

int main(void)  
{  
  int      i;  
  pthread_t threads[3];  
 
  pthread_create(&threads[2],NULL, (void *) watch_count, &thread_ids[2]);  
  pthread_create(&threads[0],NULL, (void *) inc_count, &thread_ids[0]);  
  pthread_create(&threads[1],NULL, (void *) inc_count, &thread_ids[1]);  
   
  for ( i = 0; i < 3; i++ )
    pthread_join(threads[i], NULL);  
  
  printf("r = %d\n", r);

  //for (int j = 0; j < 100000; j++ );
  //usleep(100000);
  //sleep(1);
   return 0;  
}  

void watch_count(int *idp)  
{  
  pthread_mutex_lock(&count_mutex);
    
  if (count <= WATCH_COUNT) {

    //thread = pthread_self();

    //if (! flag ) {

    //if ( thread == thread_ids[1] ) {
    //	flag = 1;
    //	pthread_cond_wait(&count_threshold_cv, &count_mutex);
    //}

    //else if  (flag == 1 && thread != thread_ids[1] )
    //	pthread_cond_wait(&count_threshold_cv, &count_mutex);
    //}

    //else if  (flag == 1 && thread != thread1 )
    flag = 1;
    pthread_cond_wait(&count_threshold_cv, &count_mutex);
      //}
    
    printf("watch_count(): Thread %d,Count is %d\n", *idp, count);
    fflush(stdout);
    r = 1;
  }  
  pthread_mutex_unlock(&count_mutex);  
}  

void inc_count(int *idp)  
{  
  int i;

  //for ( i = 0; i < 10000; i++ );
  //usleep(10);

  pthread_mutex_lock(&count_mutex);  
  
  if  ( flag ) {
    for ( i = 0; i < TCOUNT; i++ ) {  
      count++;  
      printf("inc_count(): Thread %d, old count %d,new count %d\n", 
	     *idp, count - 1, count );  
      
      if (count == WATCH_COUNT)   {
	pthread_cond_signal(&count_threshold_cv);  
	//pthread_cond_broadcast(&count_threshold_cv);  
      }

      //sleep(1);
      //for (int j = 0; j < 10000000; j++ );
      //usleep(10000);
    }
  }
  pthread_mutex_unlock(&count_mutex);

  //for (int j = 0; j < 10000000; j++ );
  //sleep(1);

} 
 

