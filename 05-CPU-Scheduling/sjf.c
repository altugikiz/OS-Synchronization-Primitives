#include <stdio.h>

/*
 * Chapter 6: CPU Scheduling - SJF (Shortest Job First) - Non-Preemptive
 * Referans: Silberschatz, Galvin and Gagne ©2013 - Slide 6.13, 6.14
 *
 * Mantık:
 * CPU burst süresi en küçük olan işlemi seçer[cite: 171].
 * Ortalama bekleme süresi açısından optimaldir.
 */

typedef struct
{
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void sort_by_burst_time(Process p[], int n)
{
    // Bubble Sort ile Burst Time'a göre sırala (Küçükten büyüğe)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].burst_time > p[j + 1].burst_time)
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void calculate_times(Process p[], int n)
{
    p[0].waiting_time = 0;
    p[0].turnaround_time = p[0].burst_time;

    for (int i = 1; i < n; i++)
    {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

int main()
{
    // Slayt 6.14'teki Örnek Veriler
    Process processes[] = {
        {1, 6, 0, 0},
        {2, 8, 0, 0},
        {3, 7, 0, 0},
        {4, 3, 0, 0}};
    int n = sizeof(processes) / sizeof(processes[0]);

    printf("--- SJF (Non-Preemptive) Simulation ---\n");

    // Önce sırala (SJF'nin kuralı)
    sort_by_burst_time(processes, n);

    // Sonra hesapla
    calculate_times(processes, n);

    // Sonuçları yazdır
    printf("PID\tBurst\tWaiting\tTurnaround\n");
    printf("---\t-----\t-------\t----------\n");
    float total_wait = 0;
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\n",
               processes[i].id, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
        total_wait += processes[i].waiting_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wait / n);

    return 0;
}