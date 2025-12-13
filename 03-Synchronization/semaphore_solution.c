#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Chapter 5: Synchronization - Semaphore Solution
 * Reference: Silberschatz, Galvin and Gagne ©2013 - Slides 5.25, 5.26
 *
 * Description:
 * This program uses a Binary Semaphore to enforce Mutual Exclusion.
 * A Binary Semaphore behaves similarly to a Mutex Lock but can be used
 * for more complex signaling patterns.
 *
 * Mechanism:
 * - sem_wait(): Decrements value. If value < 0, block. (Entry Section) [cite_start][cite: 965]
 * - sem_post(): Increments value. Wakes up a blocked process. (Exit Section) [cite_start][cite: 971]
 */

#define ITERATIONS 1000000

long shared_counter = 0;

// Define the Semaphore
sem_t binary_sem;

void *increment_with_semaphore(void *param)
{
    for (int i = 0; i < ITERATIONS; i++)
    {

        // --- ENTRY SECTION ---
        // Wait (P operation). If sem == 1, it becomes 0 and we proceed.
        // If sem == 0, we block until it becomes 1.
        sem_wait(&binary_sem);

        // --- CRITICAL SECTION ---
        shared_counter++;

        // --- EXIT SECTION ---
        // Signal (V operation). Set sem = 1 and wake up waiting threads.
        sem_post(&binary_sem);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    // Initialize Semaphore
    // 0 = Shared between threads
    [cite_start] // 1 = Initial value (Binary Semaphore / Available) [cite: 979]
        sem_init(&binary_sem, 0, 1);

    printf("--- Semaphore Solution Started ---\n");

    pthread_create(&t1, NULL, increment_with_semaphore, NULL);
    pthread_create(&t2, NULL, increment_with_semaphore, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&binary_sem);

    printf("Expected Value: %d\n", ITERATIONS * 2);
    printf("Actual Value  : %ld\n", shared_counter);

    if (shared_counter == ITERATIONS * 2)
    {
        printf("✅ SUCCESS: Data consistency maintained using Binary Semaphore.\n");
    }
    else
    {
        printf("❌ FAILURE: Race condition still exists.\n");
    }

    return 0;
}