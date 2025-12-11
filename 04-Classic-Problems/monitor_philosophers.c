#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Chapter 5: Monitor Solution to Dining Philosophers
 * * Bu kod, Slayt 5.48 ve 5.49'daki Monitor yapısını C ve Pthreads
 * kütüphanesi kullanarak simüle eder.
 * * Yöntem: Condition Variables (Koşul Değişkenleri) kullanımı.
 * Referans: Silberschatz, Galvin and Gagne ©2013 - Slides 5.48, 5.49
 */

#define N 5 // Filozof Sayısı

// Filozof Durumları (Slayt 5.48)
#define THINKING 0
#define HUNGRY 1
#define EATING 2

// Monitor Kilidi (C'de 'monitor' keyword'ü olmadığı için Mutex kullanıyoruz)
pthread_mutex_t monitor_lock;

// Condition Variables (Slayt: condition self[5])
// Filozofların sırasını beklerken uyutulması için kullanılır.
pthread_cond_t self[N];

// Paylaşılan Durum Dizisi
int state[N];
int philosopher_ids[N];

// ------------------------------------------------------------------
// Test Fonksiyonu (Slayt 5.49)
// Filozofun yemek yiyip yiyemeyeceğini (komşularına bakarak) kontrol eder.
// ------------------------------------------------------------------
void test(int i) {
    // Sol komşu: (i + 4) % 5
    // Sağ komşu: (i + 1) % 5
    if ((state[(i + 4) % N] != EATING) &&
        (state[i] == HUNGRY) &&
        (state[(i + 1) % N] != EATING)) {
            
        state[i] = EATING;
        
        // Eğer yemek yiyebiliyorsa, bekleyen filozofu uyandır (signal)
        pthread_cond_signal(&self[i]);
    }
}

// ------------------------------------------------------------------
// Pickup Fonksiyonu (Slayt 5.48)
// Filozof acıktığında çağrılır.
// ------------------------------------------------------------------
void pickup(int i) {
    pthread_mutex_lock(&monitor_lock); // Monitor giriş (Kritik Bölge Başlangıcı)

    state[i] = HUNGRY;
    printf("Filozof %d: Acikti (HUNGRY), catal istiyor...\n", i);
    
    test(i);

    // Eğer yemek yeme durumuna geçemediysem, sıram gelene kadar uyu.
    // Slayt: if (state[i] != EATING) self[i].wait;
    while (state[i] != EATING) {
        pthread_cond_wait(&self[i], &monitor_lock);
    }

    pthread_mutex_unlock(&monitor_lock); // Monitor çıkış
}

// ------------------------------------------------------------------
// Putdown Fonksiyonu (Slayt 5.48)
// Filozof yemeğini bitirdiğinde çağrılır.
// ------------------------------------------------------------------
void putdown(int i) {
    pthread_mutex_lock(&monitor_lock); // Monitor giriş

    state[i] = THINKING;
    printf("Filozof %d: Yemegi bitirdi, catallari birakti (THINKING).\n", i);

    // Sağ ve Sol komşularıma haber ver (Belki onlar yemek istiyordur)
    test((i + 4) % N);
    test((i + 1) % N);

    pthread_mutex_unlock(&monitor_lock); // Monitor çıkış
}

// ------------------------------------------------------------------
// Filozof Thread Fonksiyonu
// ------------------------------------------------------------------
void* philosopher(void* num) {
    int id = *((int*)num);

    while (1) {
        // Düşünme Aşaması
        int think_time = rand() % 3 + 1;
        sleep(think_time);

        // Yemek Alma (Monitor Entry)
        pickup(id);

        // Yemek Yeme Aşaması
        printf("Filozof %d: YEMEK YIYOR 🍝\n", id);
        sleep(2);

        // Yemek Bırakma (Monitor Exit)
        putdown(id);
    }
}

int main() {
    // 1. Monitor Araçlarını Başlat
    pthread_mutex_init(&monitor_lock, NULL);
    for (int i = 0; i < N; i++) {
        pthread_cond_init(&self[i], NULL);
        state[i] = THINKING;
        philosopher_ids[i] = i;
    }

    pthread_t thread_id[N];

    printf("--- Dining Philosophers (Monitor Solution) Baslatiliyor ---\n");

    // 2. Threadleri Oluştur
    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // 3. Threadleri Bekle (Sonsuz döngü olduğu için program buradan çıkmaz)
    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}