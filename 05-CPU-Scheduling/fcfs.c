#include <stdio.h>

/*
 * Chapter 6: CPU Scheduling - FCFS (First-Come, First-Served)
 * Referans: Silberschatz, Galvin and Gagne ©2013 - Slide 6.11
 *
 * Mantık:
 * Ready kuyruğuna ilk giren process, CPU'yu ilk alır[cite: 129].
 * Non-preemptive (kesintisiz) bir algoritmadır[cite: 139].
 * Dezavantajı: "Convoy Effect" (Kısa işler, uzun işin bitmesini bekler)[cite: 148].
 */

typedef struct
{
    int id;
    int burst_time;      // İşlemcinin ne kadar süreye ihtiyacı var?
    int waiting_time;    // Sırada ne kadar bekledi?
    int turnaround_time; // Toplamda ne kadar sürede bitti?
} Process;

void calculate_times(Process p[], int n)
{
    // İlk process hiç beklemez
    p[0].waiting_time = 0;
    p[0].turnaround_time = p[0].burst_time;

    // Diğer process'ler için hesaplama
    for (int i = 1; i < n; i++)
    {
        // Bekleme süresi = Önceki işlemin bekleme süresi + Önceki işlemin burst süresi
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;

        // Turnaround süresi = Bekleme süresi + Kendi burst süresi
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

void print_table(Process p[], int n)
{
    printf("PID\tBurst\tWaiting\tTurnaround\n");
    printf("---\t-----\t-------\t----------\n");

    float total_wait = 0, total_turnaround = 0;

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\n",
               p[i].id, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
        total_wait += p[i].waiting_time;
        total_turnaround += p[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wait / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

int main()
{
    // Örnek Processler (Slayt 6.11'deki değerlere benzer)
    Process processes[] = {
        {1, 24, 0, 0},
        {2, 3, 0, 0},
        {3, 3, 0, 0}};
    int n = sizeof(processes) / sizeof(processes[0]);

    printf("--- FCFS Scheduling Simulation ---\n");
    calculate_times(processes, n);
    print_table(processes, n);

    return 0;
}