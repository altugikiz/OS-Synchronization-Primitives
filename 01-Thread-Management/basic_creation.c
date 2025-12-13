#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Chapter 4: Threads - Basic Thread Management
 * Reference: Silberschatz, Galvin and Gagne ©2013 - Slides 4.20, 4.21, 4.22
 *
 * Concepts Demonstrated:
 * 1. Thread Creation (pthread_create) - [cite: 271]
 * 2. Thread Joining (pthread_join) - [cite: 273]
 * 3. Thread Exiting (pthread_exit) - [cite: 282]
 */

#define NUM_THREADS 5

// The function that each thread will execute (The "Runner")
// Reference: Slide 4.20 - void *runner(void *param); [cite: 252]
void *runner(void *param)
{
    long thread_id = (long)param;

    printf("Thread %ld: Started execution...\n", thread_id);

    // Simulate some work being done (e.g., fetching data, processing image)
    int work_time = rand() % 3 + 1;
    sleep(work_time);

    printf("Thread %ld: Finished work in %d seconds.\n", thread_id, work_time);

    // Exit the thread
    pthread_exit(0);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    printf("--- Main Process: Spawning %d threads ---\n", NUM_THREADS);

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Main: Creating thread %ld\n", t);

        // Create a new thread
        // &threads[t]: Thread ID
        // NULL: Default attributes (Slide 4.21) [cite: 268]
        // runner: The function to execute
        // (void *)t: Argument passed to the function
        rc = pthread_create(&threads[t], NULL, runner, (void *)t);

        if (rc)
        {
            printf("Error: Unable to create thread, %d\n", rc);
            exit(-1);
        }
    }

    printf("--- Main Process: Waiting for threads to finish (Join) ---\n");

    // Wait for all threads to complete
    // Reference: Slide 4.22 - Joining threads [cite: 290]
    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
        printf("Main: Thread %ld has joined (completed).\n", t);
    }

    printf("--- Main Process: All threads completed. Exiting. ---\n");
    return 0;
} 