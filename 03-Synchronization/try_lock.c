#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*
 * Chapter 5: Synchronization - Try Lock (Deadlock Avoidance)
 * Reference: Related to "Deadlock and Starvation" - Slide 5.30
 *
 * Description:
 * Standard `pthread_mutex_lock` blocks the thread if the lock is not available.
 * `pthread_mutex_trylock` returns immediately with an error (EBUSY) if locked.
 *
 * Scenario:
 * A "Thief" thread tries to steal a treasure (counter).
 * A "Police" thread guards it.
 * If the Thief finds the lock busy (Police is there), he runs away instead of waiting.
 */

pthread_mutex_t treasure_lock;
int treasure_chest = 1000;

void *police_officer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&treasure_lock);
        printf("👮 Police: I am guarding the treasure...\n");
        sleep(2); // Guards for 2 seconds
        pthread_mutex_unlock(&treasure_lock);
        printf("👮 Police: Taking a coffee break.\n");
        sleep(2); // Break for 2 seconds
    }
    return NULL;
}

void *thief(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        // Try to steal (Non-blocking lock attempt)
        int status = pthread_mutex_trylock(&treasure_lock);

        if (status == 0)
        {
            // Success! We got the lock.
            printf("🦹 Thief %d: Haha! I stole some gold!\n", id);
            treasure_chest -= 50;
            printf("   Remaining Treasure: %d\n", treasure_chest);
            pthread_mutex_unlock(&treasure_lock);
        }
        else if (status == EBUSY)
        {
            // Lock is busy
            printf("🦹 Thief %d: Police is watching! I'll come back later.\n", id);
        }
        else
        {
            perror("Mutex error");
        }

        sleep(1); // Wait a bit before trying again
    }
    return NULL;
}

int main()
{
    pthread_t police, thief1;
    int id1 = 1;

    pthread_mutex_init(&treasure_lock, NULL);

    pthread_create(&police, NULL, police_officer, NULL);
    pthread_create(&thief1, NULL, thief, &id1);

    // Let simulation run for 10 seconds
    sleep(10);

    printf("--- Simulation Over ---\n");
    return 0;
}