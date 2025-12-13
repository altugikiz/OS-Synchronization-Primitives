#include <stdio.h>
#include <stdbool.h>

/*
 * Chapter 6: CPU Scheduling - Round Robin (RR)
 * Referans: Silberschatz, Galvin and Gagne ©2013 - Slide 6.21
 *
 * Mantık:
 * Her işleme küçük bir CPU zaman birimi (Time Quantum, q) verilir[cite: 324].
 * Süre dolunca işlem kesilir (preempted) ve kuyruğun sonuna atılır[cite: 325].
 * Windows ve Linux gibi modern sistemler için temeldir.
 */

typedef struct
{
    int id;
    int burst_time;
    int remaining_time; // Kalan süre (RR için gerekli)
    int waiting_time;
    int turnaround_time;
} Process;

void calculate_rr(Process p[], int n, int quantum)
{
    int time = 0; // Şimdiki zaman
    int completed = 0;

    // Kalan süreleri başlat
    for (int i = 0; i < n; i++)
        p[i].remaining_time = p[i].burst_time;

    // Tüm işlemler bitene kadar dön
    while (completed < n)
    {
        bool done_something = false;

        for (int i = 0; i < n; i++)
        {
            if (p[i].remaining_time > 0)
            {
                done_something = true;

                if (p[i].remaining_time > quantum)
                {
                    // Quantum kadar çalış, sonra sırayı sal
                    time += quantum;
                    p[i].remaining_time -= quantum;
                }
                else
                {
                    // Quantum'dan az kaldıysa bitir
                    time += p[i].remaining_time;
                    p[i].waiting_time = time - p[i].burst_time;
                    p[i].remaining_time = 0;
                    completed++;
                }
            }
        }
        if (!done_something)
            break;
    }

    // Turnaround hesapla
    for (int i = 0; i < n; i++)
        p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
}

int main()
{
    // Slayt 6.23'teki Örnek (Quantum = 4)
    Process processes[] = {
        {1, 24, 0, 0, 0},
        {2, 3, 0, 0, 0},
        {3, 3, 0, 0, 0}};
    int n = sizeof(processes) / sizeof(processes[0]);
    int quantum = 4;

    printf("--- Round Robin Simulation (Quantum = %d) ---\n", quantum);

    calculate_rr(processes, n, quantum);

    printf("PID\tBurst\tWaiting\tTurnaround\n");
    printf("---\t-----\t-------\t----------\n");
    float total_wait = 0;
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\n",
               processes[i].id, processes[i].burst_time,
               processes[i].waiting_time, processes[i].turnaround_time);
        total_wait += processes[i].waiting_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wait / n);

    return 0;
}