# Lab 2 & 3: Process Creation and CPU Scheduling Algorithms

## Overview
This folder contains implementations for Operating System Lab 2 and Lab 3 assignments.

### Lab 2: Understanding fork() and Process Creation
Programs demonstrating how `fork()` system call creates new processes.

### Lab 3: CPU Scheduling Algorithms
Simulation of various CPU scheduling algorithms with Gantt chart visualization.

---

## Folder Structure

```
Lab_2_and_3/
├── source_code/          # All C source files
│   ├── lab2_program1_original.c
│   ├── lab2_partA_two_forks.c
│   ├── lab2_partB_three_forks.c
│   ├── lab2_program2_pid.c
│   ├── lab3_fcfs_scheduling.c
│   ├── lab3_sjf_scheduling.c
│   ├── lab3_srtf_scheduling.c
│   └── lab3_round_robin_scheduling.c
├── executables/          # Compiled programs
└── LAB_GUIDE.md         # Comprehensive guide with explanations
```

---

## Lab 2 Programs

### Program 1: Basic fork() Demonstration
- **lab2_program1_original.c** - 1 fork() → 2 processes (2 "Hello world" outputs)
- **lab2_partA_two_forks.c** - 2 fork() → 4 processes (4 outputs)
- **lab2_partB_three_forks.c** - 3 fork() → 8 processes (8 outputs)

### Program 2: Parent/Child Identification
- **lab2_program2_pid.c** - Demonstrates how parent and child identify themselves using PID

---

## Lab 3 Programs

### 1. FCFS (First Come First Serve)
- **File:** `lab3_fcfs_scheduling.c`
- **Type:** Non-preemptive
- **Use:** Simple, no starvation

### 2. SJF (Shortest Job First)
- **File:** `lab3_sjf_scheduling.c`
- **Type:** Non-preemptive
- **Use:** Minimizes average waiting time

### 3. SRTF (Shortest Remaining Time First)
- **File:** `lab3_srtf_scheduling.c`
- **Type:** Preemptive
- **Use:** Better for varying arrival times

### 4. Round Robin
- **File:** `lab3_round_robin_scheduling.c`
- **Type:** Preemptive with time quantum
- **Use:** Fair scheduling for interactive systems

---

## How to Compile and Run

### Compile All Programs
```bash
cd source_code

# Lab 2 Programs
gcc -o ../executables/program lab2_program1_original.c
gcc -o ../executables/partA lab2_partA_two_forks.c
gcc -o ../executables/partB lab2_partB_three_forks.c
gcc -o ../executables/prog2 lab2_program2_pid.c

# Lab 3 Programs
gcc -o ../executables/fcfs lab3_fcfs_scheduling.c
gcc -o ../executables/sjf lab3_sjf_scheduling.c
gcc -o ../executables/srtf lab3_srtf_scheduling.c
gcc -o ../executables/rr lab3_round_robin_scheduling.c
```

### Run Programs
```bash
cd executables

# Lab 2
./program
./partA
./partB
./prog2

# Lab 3 (interactive - requires input)
./fcfs
./sjf
./srtf
./rr
```

---

## Key Concepts

### Fork() Formula
With `n` sequential fork() calls: **Total Processes = 2^n**

### Scheduling Comparison

| Algorithm | Type | Best For | Starvation |
|-----------|------|----------|------------|
| FCFS | Non-preemptive | Simple systems | No |
| SJF | Non-preemptive | Batch processing | Yes (long jobs) |
| SRTF | Preemptive | Variable workloads | Yes (long jobs) |
| Round Robin | Preemptive | Interactive systems | No |

---

## Documentation
See **LAB_GUIDE.md** for:
- Detailed explanations of fork() behavior
- Process tree diagrams
- Complete scheduling algorithm analysis
- Sample outputs and calculations

---

**Author:** Operating Systems Lab Course  
**Date:** January 2026
