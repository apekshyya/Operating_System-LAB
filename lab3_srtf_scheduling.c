#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival;
    int bt;
    int remaining;
    int wt;
    int tat;
    int completion;
} Process;

int main() {
    int n, i, time = 0, completed = 0;
    int total_wt = 0, total_tat = 0;
    
    printf("SRTF (Shortest Remaining Time First) Scheduling Algorithm\n");
    printf("=========================================================\n\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process p[n];
    
    // Input burst times (assuming arrival time is 0 for all)
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].arrival = 0;  // All processes arrive at time 0
        p[i].completion = 0;
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].remaining = p[i].bt;
    }
    
    printf("\nSRTF Scheduling (Preemptive):\n");
    printf("============================\n");
    printf("Time 0-");
    
    // SRTF Algorithm
    while (completed < n) {
        int idx = -1;
        int minRemaining = 999;
        
        // Find process with minimum remaining time
        for (i = 0; i < n; i++) {
            if (p[i].remaining > 0 && p[i].remaining < minRemaining) {
                minRemaining = p[i].remaining;
                idx = i;
            }
        }
        
        if (idx == -1) break;
        
        p[idx].remaining--;
        time++;
        
        // If process is completed
        if (p[idx].remaining == 0) {
            completed++;
            p[idx].completion = time;
            p[idx].tat = p[idx].completion - p[idx].arrival;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
        }
    }
    
    printf("%d: Process execution complete\n\n", time);
    
    printf("%-10s%-15s%-15s%-15s\n", "Process", "Burst Time", "Waiting Time", "Turnaround Time");
    printf("-------------------------------------------------------\n");
    
    for (i = 0; i < n; i++) {
        printf("P%-9d%-15d%-15d%-15d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }
    
    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);
    
    return 0;
}
