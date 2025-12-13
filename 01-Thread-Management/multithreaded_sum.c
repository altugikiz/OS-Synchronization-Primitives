#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Chapter 4: Threads - Multithreading & Data Parallelism
 * Reference: Silberschatz, Galvin and Gagne ©2013 - Slide 4.8
 *
 * Scenario:
 * Calculating the sum of an array is a task that can be parallelized.
 * We split the array into two halves.
 * - Thread 1 sums the first half.
 * - Thread 2 sums the second half.
 * - Main thread adds the two partial sums.
 */

#define ARRAY_SIZE 1000
#define NUM_THREADS 2

// Shared data array
int data[ARRAY_SIZE];

// Structure to pass arguments to threads
typedef struct
{
    int start_index;
    int end_index;
    long long partial_sum;
} ThreadData;

ThreadData thread_data[NUM_THREADS];

// The Runner Function
void *sum_runner(void *arg)
{
    ThreadData *t_data = (ThreadData *)arg;
    t_data->partial_sum = 0;

    // Calculate sum for the assigned range
    for (int i = t_data->start_index; i < t_data->end_index; i++)
    {
        t_data->partial_sum += data[i];
    }

    printf("Thread (Range %d-%d): Partial Sum = %lld\n",
           t_data->start_index, t_data->end_index, t_data->partial_sum);

    pthread_exit(0);
}

int main()
{
    pthread_t threads[NUM_THREADS];

    // 1. Initialize the array with some values (e.g., 1, 2, 3...)
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        data[i] = i + 1; // 1 to 1000
    }

    // 2. Define ranges for threads (Data Splitting - Slide 4.7) [cite: 64]
    // Thread 0: 0 to 499
    thread_data[0].start_index = 0;
    thread_data[0].end_index = ARRAY_SIZE / 2;

    // Thread 1: 500 to 1000
    thread_data[1].start_index = ARRAY_SIZE / 2;
    thread_data[1].end_index = ARRAY_SIZE;

    // 3. Create Threads
    printf("--- Main: Starting Parallel Summation ---\n");
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, sum_runner, &thread_data[i]);
    }

    // 4. Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // 5. Combine Results (Reduction)
    long long total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        total_sum += thread_data[i].partial_sum;
    }

    // Validation (Formula: n(n+1)/2)
    long long expected_sum = (long long)ARRAY_SIZE * (ARRAY_SIZE + 1) / 2;

    printf("--- Result ---\n");
    printf("Total Sum (Calculated): %lld\n", total_sum);
    printf("Total Sum (Expected)  : %lld\n", expected_sum);

    return 0;
}