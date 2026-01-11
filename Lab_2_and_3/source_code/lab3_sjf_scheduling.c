#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int bt;
    int wt;
    int tat;
} Process;

int compare(const void *a, const void *b) {
    return ((Process*)a)->bt - ((Process*)b)->bt;
}

int main() {
    int n, i;
    int total_wt = 0, total_tat = 0;
    
    printf("SJF (Shortest Job First) Scheduling Algorithm\n");
    printf("==============================================\n\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process p[n];
    
    // Input burst times
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &p[i].bt);
    }
    
    // Sort by burst time (Shortest Job First)
    qsort(p, n, sizeof(Process), compare);
    
    // Calculate waiting time and turnaround time
    p[0].wt = 0;
    for (i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }
    
    printf("\n%-10s%-15s%-15s%-15s\n", "Process", "Burst Time", "Waiting Time", "Turnaround Time");
    printf("-------------------------------------------------------\n");
    
    for (i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        printf("P%-9d%-15d%-15d%-15d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }
    
    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);
    
    // Gantt Chart
    printf("\nGantt Chart:\n");
    printf("|");
    for (i = 0; i < n; i++) {
        printf(" P%d |", p[i].pid);
    }
    printf("\n");
    
    printf("0");
    for (i = 0; i < n; i++) {
        printf("     %d", p[i].wt + p[i].bt);
    }
    printf("\n");
    
    return 0;
}
