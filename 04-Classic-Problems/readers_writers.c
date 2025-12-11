#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Slayt Referansı: 5.35 - Readers-Writers Problem [cite: 1106]
 * Kural: Birden fazla okuyucu aynı anda okuyabilir, ama yazar tek başınadır.
 */

// Paylaşılan Veri
int shared_data = 0;
int read_count = 0; // Kaç tane okuyucu içeride? [cite: 1119]

// Kilitler
pthread_mutex_t mutex;    // read_count değişkenini korur [cite: 1118]
pthread_mutex_t rw_mutex; // Yazma işlemi ve ilk okuyucu için kilit [cite: 1117]

void* writer(void* param) {
    int id = *((int*)param);
    // Slayt 5.36: Writer Process [cite: 1124]
    printf("Writer %d: Yazmak istiyor...\n", id);
    
    pthread_mutex_lock(&rw_mutex); // Yazma izni iste
    
    // CRITICAL SECTION (YAZMA)
    shared_data++;
    printf("Writer %d: Veriyi güncelledi -> %d\n", id, shared_data);
    sleep(1); 
    
    pthread_mutex_unlock(&rw_mutex); // İzni bırak
    return NULL;
}

void* reader(void* param) {
    int id = *((int*)param);
    // Slayt 5.37: Reader Process [cite: 1134]
    
    // 1. Okuyucu Giriş Protokolü
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        pthread_mutex_lock(&rw_mutex); // İlk okuyucuysan, yazarı engelle [cite: 1138]
    }
    pthread_mutex_unlock(&mutex);

    // CRITICAL SECTION (OKUMA)
    printf("Reader %d: Okuyor -> %d (Aktif Okuyucu: %d)\n", id, shared_data, read_count);
    sleep(1);

    // 2. Okuyucu Çıkış Protokolü
    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        pthread_mutex_unlock(&rw_mutex); // Son okuyucuysan, yazara izin ver [cite: 1145]
    }
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    int ids[5] = {1, 2, 3, 4, 5};

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&rw_mutex, NULL);

    // Karışık sırada başlat
    pthread_create(&r[0], NULL, reader, &ids[0]);
    pthread_create(&w[0], NULL, writer, &ids[0]);
    pthread_create(&r[1], NULL, reader, &ids[1]);
    pthread_create(&r[2], NULL, reader, &ids[2]);
    pthread_create(&w[1], NULL, writer, &ids[1]);
    pthread_create(&r[3], NULL, reader, &ids[3]);

    for(int i=0; i<4; i++) pthread_join(r[i], NULL);
    for(int i=0; i<2; i++) pthread_join(w[i], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&rw_mutex);

    return 0;
}