#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Chapter 5: Dining Philosophers Problem (Mutex Solution)
 *
 * Problem Tanımı: 5 Filozof, 5 Çatal. Yemek yemek için 2 çatala ihtiyaç var.
 * Referans: Silberschatz, Galvin and Gagne ©2013 - Slide 5.39
 *
 * Çözüm Yöntemi: Asymmetric Solution (Slide 5.41)
 * - Deadlock (Kilitlenme) oluşumunu engellemek için:
 * - Tek numaralı filozoflar önce SOL, sonra SAĞ çatalı alır.
 * - Çift numaralı filozoflar önce SAĞ, sonra SOL çatalı alır.
 */

#define N 5 // Filozof ve Çatal Sayısı

// Her çatal bir Mutex ile temsil edilir
pthread_mutex_t chopsticks[N];

void* philosopher(void* num) {
    int id = *((int*)num);
    
    // Çatal İndeksleri
    int left_fork = id;
    int right_fork = (id + 1) % N;

    while (1) {
        // 1. DÜŞÜNME (Thinking)
        printf("Filozof %d: Dusunuyor...\n", id);
        sleep(1 + rand() % 2); // Rastgele bekleme

        printf("Filozof %d: Acikti, catal almaya calisiyor.\n", id);

        // 2. ÇATAL ALMA (Picking up chopsticks)
        // Slide 5.41: Asimetrik Çözüm Uygulanıyor
        if (id % 2 != 0) {
            // Tek Numaralılar (Odd): Önce SOL -> Sonra SAĞ
            pthread_mutex_lock(&chopsticks[left_fork]);
            printf("Filozof %d: Sol catali (%d) aldi.\n", id, left_fork);
            
            pthread_mutex_lock(&chopsticks[right_fork]);
            printf("Filozof %d: Sag catali (%d) aldi.\n", id, right_fork);
        } else {
            // Çift Numaralılar (Even): Önce SAĞ -> Sonra SOL
            pthread_mutex_lock(&chopsticks[right_fork]);
            printf("Filozof %d: Sag catali (%d) aldi.\n", id, right_fork);
            
            pthread_mutex_lock(&chopsticks[left_fork]);
            printf("Filozof %d: Sol catali (%d) aldi.\n", id, left_fork);
        }

        // 3. YEMEK YEME (Eating)
        printf("Filozof %d: YEMEK YIYOR 🍝\n", id);
        sleep(2); // Yemek süresi

        // 4. ÇATAL BIRAKMA (Putting down chopsticks)
        // Sırası önemli değil ama aldığımız kilitleri bırakıyoruz.
        pthread_mutex_unlock(&chopsticks[left_fork]);
        pthread_mutex_unlock(&chopsticks[right_fork]);
        
        printf("Filozof %d: Yemek bitti, catallari birakti.\n", id);
    }

    return NULL;
}

int main() {
    pthread_t philo[N];
    int ids[N];

    printf("--- Dining Philosophers (Mutex - Asymmetric Solution) ---\n");

    // Mutexleri (Çatalları) Başlat
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
        ids[i] = i;
    }

    // Filozofları Masaya Oturt (Thread Oluştur)
    for (int i = 0; i < N; i++) {
        int ret = pthread_create(&philo[i], NULL, philosopher, &ids[i]);
        if (ret != 0) {
            perror("Thread oluşturma hatası");
        }
    }

    // Threadleri Bekle (Sonsuz döngü)
    for (int i = 0; i < N; i++) {
        pthread_join(philo[i], NULL);
    }

    // Temizlik (Kod buraya ulaşmaz ama iyi bir alışkanlıktır)
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}