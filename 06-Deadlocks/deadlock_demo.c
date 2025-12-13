#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Chapter 7: Deadlocks - Demonstration
 * Referans: Silberschatz, Galvin and Gagne ©2013 - Slide 7.9
 *
 * Amaç: "Circular Wait" (Dairesel Bekleme) durumunu göstererek
 * sistemin nasıl kilitlendiğini (Deadlock) kanıtlamak.
 *
 * Dikkat: Bu programı çalıştırdığınızda ASLA bitmeyecek (hang).
 * Durdurmak için Terminal'de CTRL+C yapmanız gerekecek.
 */

pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;

void *thread_one_func(void *param)
{
    // 1. Kaynağı al
    pthread_mutex_lock(&first_mutex);
    printf("Thread 1: first_mutex'i aldı.\n");

    // Context switch simülasyonu (Diğer thread'in çalışmasına fırsat ver)
    sleep(1);

    printf("Thread 1: second_mutex'i istiyor... (Bekliyor)\n");
    // 2. Kaynağı iste (Ama Thread 2 tutuyor!)
    pthread_mutex_lock(&second_mutex);

    // Buraya asla ulaşamayacak (Deadlock)
    printf("Thread 1: İki kilidi de aldı!\n");

    pthread_mutex_unlock(&second_mutex);
    pthread_mutex_unlock(&first_mutex);
    return NULL;
}

void *thread_two_func(void *param)
{
    // 2. Kaynağı al (Tersten alıyor - Circular Wait sebebi)
    pthread_mutex_lock(&second_mutex);
    printf("Thread 2: second_mutex'i aldı.\n");

    sleep(1);

    printf("Thread 2: first_mutex'i istiyor... (Bekliyor)\n");
    // 1. Kaynağı iste (Ama Thread 1 tutuyor!)
    pthread_mutex_lock(&first_mutex);

    // Buraya asla ulaşamayacak
    printf("Thread 2: İki kilidi de aldı!\n");

    pthread_mutex_unlock(&first_mutex);
    pthread_mutex_unlock(&second_mutex);
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);

    printf("--- Deadlock Demo Başlıyor ---\n");
    printf("Program kilitlenecek, çıkmak için CTRL+C kullanın.\n");

    pthread_create(&t1, NULL, thread_one_func, NULL);
    pthread_create(&t2, NULL, thread_two_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}