#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Chapter 5: Process Synchronization - Race Condition Demonstration
 * Reference: Silberschatz, Galvin and Gagne ©2013 - Slide 5.7
 *
 * Description:
 * This program demonstrates a Race Condition where two threads attempt to
 * increment a shared counter concurrently without synchronization.
 *
 * The operation 'counter++' is NOT atomic. It consists of 3 machine instructions:
 * 1. LOAD  register, counter
 * 2. ADD   register, 1
 * 3. STORE counter, register
 *
 * Because of context switching during these steps, the final value will likely
 * be less than expected (2,000,000).
 */

#define ITERATIONS 1000000

// Shared Data (Critical Section Resource)
long shared_counter = 0;

void *increment_counter(void *param)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        // --- CRITICAL SECTION START ---
        // This line causes the Race Condition
        shared_counter++;
        // --- CRITICAL SECTION END ---
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    printf("--- Race Condition Demo Started ---\n");
    printf("Expected Value: %d\n", ITERATIONS * 2);

    // Create two threads running the same function
    pthread_create(&t1, NULL, increment_counter, NULL);
    pthread_create(&t2, NULL, increment_counter, NULL);

    // Wait for them to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Actual Value  : %ld\n", shared_counter);

    if (shared_counter != ITERATIONS * 2)
    {
        printf("⚠️  RACE CONDITION DETECTED! The value is incorrect.\n");
        printf("   (This proves that context switching occurred mid-operation)\n");
    }
    else
    {
        printf("Luck was on your side, but the code is still unsafe.\n");
    }

    return 0;
}