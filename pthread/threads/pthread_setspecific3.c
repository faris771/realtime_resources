#include <pthread.h>
#include <stdio.h>

pthread_key_t key;

void destructor(void* value) {
    printf("Destructor called. Value: %p\n", value);
}

void* thread_function(void* arg) {
    int* value = (int*)arg;
    pthread_setspecific(key, value);
    printf("Thread-specific value set: %p\n", value);

    // Access the thread-specific value
    int* retrieved_value = (int*)pthread_getspecific(key);
    printf("Retrieved thread-specific value: %p\n", retrieved_value);
    printf("Retrieved thread-specific value: %d\n", *retrieved_value);
    
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int value1 = 1;
    int value2 = 2;

    pthread_key_create(&key, destructor);

    pthread_create(&thread1, NULL, thread_function, (void*)&value1);
    pthread_create(&thread2, NULL, thread_function, (void*)&value2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_key_delete(key);

    return 0;
}
