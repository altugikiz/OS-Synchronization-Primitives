#include <stdio.h>
#include <stdbool.h>

/*
 * Chapter 7: Deadlock Avoidance - Banker's Algorithm
 * Referans: Silberschatz, Galvin and Gagne ©2013 - Slide 7.40 (Safety Algorithm)
 *
 * Amaç: Sistemin "Güvenli Durumda" (Safe State) olup olmadığını kontrol etmek.
 * Veriler: Slayt 7.42'deki örnek kullanılmıştır.
 * 5 Process (P0-P4) ve 3 Kaynak Tipi (A, B, C)
 */

#define N 5 // Process sayısı (P0, P1, P2, P3, P4)
#define M 3 // Kaynak tipi sayısı (A, B, C)

// Global Matrisler (Slayt 7.39)
// Allocation: Şu an kimde ne var?
int allocation[N][M] = {
    {0, 1, 0}, // P0
    {2, 0, 0}, // P1
    {3, 0, 2}, // P2
    {2, 1, 1}, // P3
    {0, 0, 2}  // P4
};

// Max: Herkes en fazla ne kadar isteyebilir?
int max[N][M] = {
    {7, 5, 3}, // P0
    {3, 2, 2}, // P1
    {9, 0, 2}, // P2
    {2, 2, 2}, // P3
    {4, 3, 3}  // P4
};

// Available: Sistemde şu an boşta ne var?
int available[M] = {3, 3, 2};

// Need: Daha ne kadar lazım? (Hesaplanacak)
int need[N][M];

void calculate_need()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            // Need = Max - Allocation (Slayt 7.43)
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void check_safe_state()
{
    int work[M];
    bool finish[N];
    int safe_sequence[N];
    int count = 0;

    // 1. Başlangıç Değerleri (Slayt 7.40 - Step 1)
    // Work = Available
    for (int i = 0; i < M; i++)
    {
        work[i] = available[i];
    }
    // Finish = false (Kimse daha bitmedi)
    for (int i = 0; i < N; i++)
    {
        finish[i] = false;
    }

    // 2. Güvenli Sıra Bulma Döngüsü
    while (count < N)
    {
        bool found = false;

        for (int p = 0; p < N; p++)
        {
            // Eğer process bitmediyse VE ihtiyacı (Need) eldekiyle (Work) karşılanabiliyorsa
            if (finish[p] == false)
            {
                int j;
                for (j = 0; j < M; j++)
                {
                    if (need[p][j] > work[j])
                        break;
                }

                // Tüm kaynak ihtiyaçları karşılanabiliyorsa (Slayt 7.40 - Step 3)
                if (j == M)
                {
                    // Kaynakları ver, process çalışsın, bitince kaynakları geri al
                    for (int k = 0; k < M; k++)
                        work[k] += allocation[p][k];

                    safe_sequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        // Eğer bir turda hiçbir process çalıştırılamadıysa -> UNSAFE
        if (found == false)
        {
            printf("Sistem GÜVENLİ DEĞİL (Unsafe State)! Deadlock ihtimali var.\n");
            return;
        }
    }

    // 3. Sonuç (Slayt 7.40 - Step 4)
    printf("Sistem GÜVENLİ (Safe State).\n");
    printf("Güvenli Sıra (Safe Sequence): ");
    for (int i = 0; i < N; i++)
    {
        printf("P%d ", safe_sequence[i]);
        if (i != N - 1)
            printf("-> ");
    }
    printf("\n");
}

int main()
{
    printf("--- Banker's Algorithm Simülasyonu ---\n");

    calculate_need();
    check_safe_state();

    return 0;
}