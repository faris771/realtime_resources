#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#ifdef __DESCRIBE_
DESCRIPTION

    The pthread_barrier_wait() function shall synchronize participating threads at the barrier referenced by barrier. The calling thread shall block until the required number of threads have called pthread_barrier_wait() specifying the barrier.

    When the required number of threads have called pthread_barrier_wait() specifying the barrier, the constant PTHREAD_BARRIER_SERIAL_THREAD shall be returned to one unspecified thread and zero shall be returned to each of the remaining threads. At this point, the barrier shall be reset to the state it had as a result of the most recent pthread_barrier_init() function that referenced it.

    The constant PTHREAD_BARRIER_SERIAL_THREAD is defined in <pthread.h> and its value shall be distinct from any other value returned by pthread_barrier_wait().

    The results are undefined if this function is called with an uninitialized barrier.

    If a signal is delivered to a thread blocked on a barrier, upon return from the signal handler the thread shall resume waiting at the barrier if the barrier wait has not completed (that is, if the required number of threads have not arrived at the barrier during the execution of the signal handler); otherwise, the thread shall continue as normal from the completed barrier wait. Until the thread in the signal handler returns from it, it is unspecified whether other threads may proceed past the barrier once they have all reached it.

    A thread that has blocked on a barrier shall not prevent any unblocked thread that is eligible to use the same processing resources from eventually making forward progress in its execution. Eligibility for processing resources shall be determined by the scheduling policy.

RETURN VALUE

    Upon successful completion, the pthread_barrier_wait() function shall return PTHREAD_BARRIER_SERIAL_THREAD for a single (arbitrary) thread synchronized at the barrier and zero for each of the other threads. Otherwise, an error number shall be returned to indicate the error.

ERRORS

    The pthread_barrier_wait() function may fail if:

    [EINVAL]
        The value specified by barrier does not refer to an initialized barrier object.

    This function shall not return an error code of [EINTR].

#endif

#define NUM_THREADS 4

pthread_barrier_t barrier;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d is doing some work\n", thread_id);
    sleep(2);
    // Wait for all threads to reach the barrier
    pthread_barrier_wait(&barrier);
    
    printf("Thread %d continues its work\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    // Initialize the barrier
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Destroy the barrier
    pthread_barrier_destroy(&barrier);
    
    return 0;
}
