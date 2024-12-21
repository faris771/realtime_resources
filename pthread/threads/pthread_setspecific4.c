#include <pthread.h>
#include <stdio.h>

pthread_key_t key;

void setThreadSpecificData(void *data) {
    pthread_setspecific(key, data);
}

void *getThreadSpecificData(void) {
    return pthread_getspecific(key);
}

int main() {
    // Create a key for thread-specific data
    pthread_key_create(&key, NULL);

    // Set thread-specific data using setThreadSpecificData function
    void *data = malloc(sizeof(void *));
    *data = (void *)42;
    setThreadSpecificData(data);

    // Retrieve thread-specific data using getThreadSpecificData function
    void *retrieved_data = getThreadSpecificData();
    if (retrieved_data) {
        printf("Thread-specific data: %p\n", retrieved_data);
    } else {
        printf("No thread-specific data found\n");
    }

    // Destroy the key
    pthread_key_destroy(key);

    return 0;
}
