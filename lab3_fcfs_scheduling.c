#include <stdio.h>

int main() {
    int n, i;
    int bt[20], wt[20], tat[20];
    int total_wt = 0, total_tat = 0;
    
    printf("FCFS (First Come First Serve) Scheduling Algorithm\n");
    printf("====================================================\n\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    // Input burst times
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }
    
    // Waiting time for first process is 0
    wt[0] = 0;
    
    // Calculate waiting time for other processes
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
    
    // Calculate turnaround time
    printf("\n%-10s%-15s%-15s%-15s\n", "Process", "Burst Time", "Waiting Time", "Turnaround Time");
    printf("-------------------------------------------------------\n");
    
    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%-9d%-15d%-15d%-15d\n", i + 1, bt[i], wt[i], tat[i]);
    }
    
    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);
    
    // Gantt Chart
    printf("\nGantt Chart:\n");
    printf("|");
    for (i = 0; i < n; i++) {
        printf(" P%d |", i + 1);
    }
    printf("\n");
    
    printf("0");
    for (i = 0; i < n; i++) {
        printf("     %d", wt[i] + bt[i]);
    }
    printf("\n");
    
    return 0;
}
