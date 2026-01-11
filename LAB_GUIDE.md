# Operating Systems Lab 2 & 3: Complete Guide
## Understanding fork() and Process Scheduling Algorithms

---

## LAB REPORT 2: PROCESS CREATION WITH fork()

### Background Concepts

**fork()** is a system call that creates a new process. When fork() is called:
- The current process (parent) is duplicated
- A new identical process (child) is created
- Both processes continue executing from the next line after fork()
- **Parent receives child's PID** (positive value)
- **Child receives 0** as return value

---

### PROGRAM 1: Basic Fork Demonstration

#### Original Program (1 fork() call)
```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("This demonstrates the fork\n");
    fork();
    printf("Hello world\n");
    return 0;
}
```

**Output:**
```
This demonstrates the fork
Hello world
Hello world
```

**Why 2 outputs?**
- Line 1: Parent prints "This demonstrates the fork"
- fork() creates a child process (both execute printf after this)
- Both parent and child print "Hello world"

**Process Tree:**
```
        Initial Process
              |
         fork() called
         /           \
    Parent          Child
    (prints)        (prints)
    Hello world     Hello world
```

---

### PART A: Two fork() Calls

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("This demonstrates the fork\n");
    fork();
    fork();
    printf("Hello world\n");
    return 0;
}
```

**Output:** 4 times "Hello world"

**Explanation:**
- First fork(): Creates 1 child (Total: 2 processes)
- Second fork(): Each of the 2 processes creates a child (Total: 4 processes)
- All 4 processes execute the printf statement
- Formula: 2^n where n = number of fork() calls

**Process Tree:**
```
                Main Process
                     |
            First fork() called
            /              \
        Parent_1         Child_1
           |               |
    Second fork()   Second fork()
      /    \          /      \
    P1_1  P1_2      C1_1    C1_2
    (P)   (C)       (C)     (C)

All 4 processes print "Hello world"
```

---

### PART B: Three fork() Calls

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("This demonstrates the fork\n");
    fork();
    fork();
    fork();
    printf("Hello world\n");
    return 0;
}
```

**Output:** 8 times "Hello world"

**Explanation:**
- 1st fork(): 2 processes
- 2nd fork(): 4 processes
- 3rd fork(): 8 processes
- Total: 2³ = 8 processes

**Key Insight:**
With n sequential fork() calls, you get 2^n total processes.

---

### PROGRAM 2: Understanding fork() with PID

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    printf("I am the parent process with ID %d\n", getpid());
    printf("Here I am before the use of forking\n");

    pid = fork();
    printf("Here I am just after forking\n");

    if (pid == 0)
        printf("I am a child process with ID %d\n", getpid());
    else
        printf("I am the parent process with PID %d\n", getpid());

    return 0;
}
```

**Sample Output:**
```
I am the parent process with ID 1234
Here I am before the use of forking
Here I am just after forking
I am the parent process with PID 1234
Here I am just after forking
I am a child process with ID 5678
```

**Key Differences:**
- **pid == 0**: This is the CHILD process
- **pid > 0**: This is the PARENT process (pid contains child's PID)
- **Different PIDs**: Each process has unique ID

**Why order might vary:**
- Parent and child execute simultaneously
- Scheduler decides which runs first
- Use synchronization for deterministic order

---

## LAB REPORT 3: PROCESS SCHEDULING ALGORITHMS

### Scheduling Concepts

**Burst Time (BT):** Time process needs CPU
**Waiting Time (WT):** Time process waits in queue
**Turnaround Time (TAT):** WT + BT (Total time from arrival to completion)

---

### 1. FCFS (First Come First Serve) - Non-Preemptive

**Algorithm:** Processes execute in arrival order, cannot be interrupted

**When to Use:** Simple, no starvation, but high average waiting time

**Example:**
```
Process | Burst Time
--------|----------
  P1    |    10
  P2    |     5
  P3    |    15
```

**Calculation:**
- P1: WT=0, TAT=10
- P2: WT=10, TAT=15
- P3: WT=15, TAT=30

**Gantt Chart:**
```
| P1  | P2 | P3  |
0    10   15    30

Average WT = (0+10+15)/3 = 8.33
Average TAT = (10+15+30)/3 = 18.33
```

**Pros:** Simple implementation
**Cons:** Convoy effect (short jobs wait for long ones)

---

### 2. SJF (Shortest Job First) - Non-Preemptive

**Algorithm:** Execute process with shortest burst time first

**When to Use:** Minimizes average waiting time

**Example (same processes):**
```
Process | Burst Time
--------|----------
  P2    |     5      (1st)
  P1    |    10      (2nd)
  P3    |    15      (3rd)
```

**Calculation:**
- P2: WT=0, TAT=5
- P1: WT=5, TAT=15
- P3: WT=15, TAT=30

**Gantt Chart:**
```
| P2 | P1  | P3  |
0    5    15    30

Average WT = (0+5+15)/3 = 6.67
Average TAT = (5+15+30)/3 = 16.67
```

**Pros:** Minimizes average WT
**Cons:** Long processes may starve, hard to know burst time

---

### 3. SRTF (Shortest Remaining Time First) - Preemptive

**Algorithm:** Interrupt current process if shorter job arrives

**When to Use:** When arrival times vary

**Example with arrival times:**
```
Process | Arrival | Burst
--------|---------|------
  P1    |    0    |  8
  P2    |    1    |  4
  P3    |    2    |  2
  P4    |    3    |  1
```

**Execution Timeline:**
- Time 0-1: P1 (8 units)
- Time 1-2: P2 (4 units) - P2 arrived, but P1 has 7 remaining (longer)
- Time 2-3: P3 (2 units) - P3 arrived with 2 remaining time
- Time 3-4: P4 (1 unit) - P4 arrived with 1 unit
- Time 4-5: P2 continues
- Time 5-9: P1 continues
- etc.

**Pros:** Minimizes WT better than SJF
**Cons:** Complex, high context switching overhead

---

### 4. Round Robin (RR) - Preemptive

**Algorithm:** Each process gets fixed time quantum (time slice)

**When to Use:** Fair scheduling, interactive systems

**Example with Quantum = 3:**
```
Process | Burst Time
--------|----------
  P1    |    8
  P2    |    4
  P3    |    2
```

**Execution:**
- Time 0-3: P1 (3 units, 5 remaining)
- Time 3-6: P2 (3 units, 1 remaining)
- Time 6-8: P3 (2 units, 0 remaining - P3 done)
- Time 8-11: P1 (3 units, 2 remaining)
- Time 11-12: P2 (1 unit, 0 remaining - P2 done)
- Time 12-14: P1 (2 units, 0 remaining - P1 done)

**Gantt Chart:**
```
| P1 | P2 | P3 | P1 | P2 | P1 |
0    3    6    8   11  12   14
```

**Pros:** Fair scheduling, no starvation
**Cons:** Longer average TAT if quantum too small/large

---

## COMPILATION AND EXECUTION

### Compile:
```bash
gcc -o program lab2_program1_original.c
gcc -o partA lab2_partA_two_forks.c
gcc -o partB lab2_partB_three_forks.c
gcc -o prog2 lab2_program2_pid.c
gcc -o fcfs lab3_fcfs_scheduling.c
gcc -o sjf lab3_sjf_scheduling.c
gcc -o srtf lab3_srtf_scheduling.c
gcc -o rr lab3_round_robin_scheduling.c
```

### Run:
```bash
./program
./partA
./partB
./prog2
./fcfs
./sjf
./srtf
./rr
```

---

## SUMMARY TABLE: Scheduling Algorithms

| Algorithm | Type | Best For | Avg WT | Starved |
|-----------|------|----------|--------|---------|
| FCFS | Non-preemptive | Simple | High | No |
| SJF | Non-preemptive | Batch | Low | Yes |
| SRTF | Preemptive | Variable | Lower | Yes |
| RR | Preemptive | Interactive | Medium | No |

---

## ANALYSIS TIPS FOR YOUR LAB REPORT

1. **Process Trees:** Draw box for each process showing parent-child relationships
2. **Explain Why:** Always explain WHY you get X outputs (e.g., 2^n formula)
3. **PID Analysis:** Show how child (pid==0) differs from parent (pid>0)
4. **Scheduling:** Calculate all metrics and compare algorithms
5. **Gantt Charts:** Visual representation helps explain concept

---

Generated: January 2026
OS Lab 2 & 3 Comprehensive Guide
