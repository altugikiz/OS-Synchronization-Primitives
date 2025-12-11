#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* * Slayt Referansı: 5.32 - Bounded-Buffer Problem [cite: 1068]
 * Amaç: Üretici (Producer) ve Tüketici (Consumer) arasında veri kaybını önlemek.
 */

#define BUFFER_SIZE 5
#define ITERATIONS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

// Senkronizasyon araçları
sem_t empty; // Boş slot sayısını tutar (Başlangıçta N) [cite: 1072]
sem_t full;  // Dolu slot sayısını tutar (Başlangıçta 0) [cite: 1071]
pthread_mutex_t mutex; // Kritik bölge kilidi (Başlangıçta 1) [cite: 1070]

void* producer(void* param) {
    int item;
    for(int i = 0; i < ITERATIONS; i++) {
        item = rand() % 100; // Rastgele bir ürün üret

        // Slayt 5.33: Producer Algoritması [cite: 1077]
        sem_wait(&empty);       // Boş yer var mı? Yoksa bekle.
        pthread_mutex_lock(&mutex); // Buffer'a erişim hakkı al.

        // CRITICAL SECTION
        buffer[in] = item;
        printf("Producer üretti: %d (Index: %d)\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Kilidi bırak.
        sem_post(&full);         // Dolu slot sayısını artır (Consumer'ı uyandır).
        
        sleep(1); // Biraz bekle
    }
    return NULL;
}

void* consumer(void* param) {
    int item;
    for(int i = 0; i < ITERATIONS; i++) {
        // Slayt 5.34: Consumer Algoritması [cite: 1093]
        sem_wait(&full);        // Dolu ürün var mı? Yoksa bekle.
        pthread_mutex_lock(&mutex); // Buffer'a erişim hakkı al.

        // CRITICAL SECTION
        item = buffer[out];
        printf("Consumer tüketti: %d (Index: %d)\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Kilidi bırak.
        sem_post(&empty);        // Boş slot sayısını artır (Producer'ı uyandır).
        
        sleep(2); // Consumer biraz yavaş olsun
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Başlatma
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE); // Empty = N [cite: 1072]
    sem_init(&full, 0, 0);            // Full = 0 [cite: 1071]

    // Threadleri oluştur
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Bekle
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Temizlik
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}