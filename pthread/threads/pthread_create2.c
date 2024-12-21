#include <stdio.h>  
#include <pthread.h>  
 
void do_one_thing(int *);  
void do_another_thing(int *);  
void do_wrap_up(int, int);
void do_wrap_up1();  

int r1 = 0, r2 = 0;  
pthread_t       thread1, thread2;  

int main(void)  
{
  int status;
  
  pthread_create(&thread1,  
	         NULL,  
		 (void *) do_one_thing,  
		 (void *) &r1);  
  

  pthread_create(&thread2,  
		 NULL,  
		 (void *) do_another_thing,  
		 (void *) &r2);  

  //pthread_join(thread2, NULL);  
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  //printf("Thread %d finished execution with status %d\n", thread1, status);

  
  do_wrap_up1();  
  
  return 0;  
} 

 
void do_one_thing(int *pnum_times)  
{  
  int i, j, x;  

  for ( i = 0;  i < 4; i++ ) {  
    printf("doing one thing\n");  
    fflush(stdout);
    
    //for ( j = 0; j < 1000; j++ );
    for ( j = 0; j < 10000000; j++ ) ;
    //x = x + i;  
    
    (*pnum_times)++;  
  }

  pthread_exit((void *) 7);
}  

void do_another_thing(int *pnum_times)  
{  
  int i, j, x, stat;  

  //pthread_join(thread1, NULL);
  //pthread_join(thread1, &stat);
  
  for ( i = 0;  i < 4; i++ ) {  
    printf("doing another \n");  
    
    for ( j = 0; j < 10000000; j++ );
    //x = x + i;

    
    (*pnum_times)++;  
  }

  pthread_exit((void *)8);
}  

void do_wrap_up1()  
{  
  int total, j;  

  //for ( j = 0; j < 100000000; j++ );
  
  printf("wrap up: one thing %d, another %d, total %d\n",  
	 r1, r2, r1 + r2);  
}

void do_wrap_up(int one_times, int another_times)  
{  
  int total, j;  

  for ( j = 0; j < 900000000; j++ );
  
  total = one_times + another_times;  
  printf("wrap up: one thing %d, another %d, total %d\n",  
	 one_times, another_times, total);  
}
