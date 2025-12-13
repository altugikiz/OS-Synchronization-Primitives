#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Chapter 5: Synchronization - Mutex Lock Solution
 * Reference: Silberschatz, Galvin and Gagne ©2013 - Slides 5.23, 5.24
 *
 * Description:
 * This program fixes the Race Condition demonstrated in '02-Race-Conditions'
 * by using a Mutex Lock (pthread_mutex_t).
 *
 * Mechanism:
 * [cite_start]1. A thread acquires the lock before entering the Critical Section[cite: 932].
 * 2. If another thread holds the lock, the requesting thread waits (sleeps).
 * [cite_start]3. After modifying the shared data, the thread releases the lock[cite: 932].
 *
 * This ensures "Mutual Exclusion", satisfying the first requirement of the
 * [cite_start]Critical Section Problem[cite: 773].
 */

#define ITERATIONS 1000000

long shared_counter = 0;

// Define the Mutex Lock
pthread_mutex_t lock;

void *increment_with_mutex(void *param)
{
    for (int i = 0; i < ITERATIONS; i++)
    {

        // --- ENTRY SECTION ---
        // Acquire the lock. If it's busy, wait here.
        // Equivalent to acquire() in Slide 5.24
        pthread_mutex_lock(&lock);

        // --- CRITICAL SECTION ---
        // Safe to modify shared data now.
        shared_counter++;

        // --- EXIT SECTION ---
        // Release the lock so other threads can enter.
        // Equivalent to release() in Slide 5.24
        pthread_mutex_unlock(&lock);

        // --- REMAINDER SECTION ---
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    // Initialize the Mutex
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex init failed\n");
        return 1;
    }

    printf("--- Mutex Solution Started ---\n");

    // Create threads
    pthread_create(&t1, NULL, increment_with_mutex, NULL);
    pthread_create(&t2, NULL, increment_with_mutex, NULL);

    // Wait for threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy the Mutex
    pthread_mutex_destroy(&lock);

    printf("Expected Value: %d\n", ITERATIONS * 2);
    printf("Actual Value  : %ld\n", shared_counter);

    if (shared_counter == ITERATIONS * 2)
    {
        printf("✅ SUCCESS: Data consistency maintained using Mutex.\n");
    }
    else
    {
        printf("❌ FAILURE: Race condition still exists.\n");
    }

    return 0;
}