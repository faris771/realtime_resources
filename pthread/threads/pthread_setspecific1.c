#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_key_t key;
void *thread_func(void *arg);

int main()
{
    pthread_t thread1, thread2;

    // Create a key for thread-specific data
    pthread_key_create(&key, NULL);

    // Create two threads
    pthread_create(&thread1, NULL, thread_func, "Thread 1");
    pthread_create(&thread2, NULL, thread_func, "Thread 2");

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the key
    pthread_key_delete(key);

    return 0;
}

void *thread_func(void *arg)
{
    char *thread_name = (char *)arg;
    int *thread_data = (int *)malloc(sizeof(int));

    // Set the thread-specific data for this thread
    pthread_setspecific(key, thread_data);

    // Get the thread-specific data for this thread
    thread_data = (int *)pthread_getspecific(key);

    printf("%s: thread-specific data = %p\n", thread_name, thread_data);

    return NULL;
}
