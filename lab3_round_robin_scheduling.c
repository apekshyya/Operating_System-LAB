#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int n, i, time = 0, completed = 0, quantum;
    int total_wt = 0, total_tat = 0;
    
    printf("Round Robin (RR) Scheduling Algorithm\n");
    printf("====================================\n\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);
    
    Process p[n];
    
    // Input burst times
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].arrival = 0;  // All processes arrive at time 0
        p[i].completion = 0;
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].remaining = p[i].bt;
    }
    
    // Round Robin scheduling
    printf("\nRound Robin Scheduling with Time Quantum = %d:\n", quantum);
    printf("==============================================\n");
    
    int queue[100];
    int qfront = 0, qrear = 0;
    
    // Initialize queue with all processes
    for (i = 0; i < n; i++) {
        queue[qrear++] = i;
    }
    
    printf("Execution Timeline:\n");
    
    while (qfront < qrear) {
        int idx = queue[qfront++];
        
        if (p[idx].remaining > 0) {
            int execute = (p[idx].remaining > quantum) ? quantum : p[idx].remaining;
            printf("P%d executes for %d units (Time %d-%d)\n", p[idx].pid, execute, time, time + execute);
            
            p[idx].remaining -= execute;
            time += execute;
            
            if (p[idx].remaining > 0) {
                queue[qrear++] = idx;  // Re-add to queue if not completed
            } else {
                p[idx].completion = time;
                p[idx].tat = p[idx].completion - p[idx].arrival;
                p[idx].wt = p[idx].tat - p[idx].bt;
                total_wt += p[idx].wt;
                total_tat += p[idx].tat;
                printf("  -> P%d completed\n", p[idx].pid);
            }
        }
    }
    
    printf("\n%-10s%-15s%-15s%-15s\n", "Process", "Burst Time", "Waiting Time", "Turnaround Time");
    printf("-------------------------------------------------------\n");
    
    for (i = 0; i < n; i++) {
        printf("P%-9d%-15d%-15d%-15d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }
    
    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);
    
    return 0;
}
