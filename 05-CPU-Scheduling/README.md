# CPU Scheduling Algorithms 📅

This directory contains C implementations of standard CPU scheduling algorithms discussed in **Chapter 6** of *Operating System Concepts*.

## Algorithms Implemented

### 1. FCFS (First-Come, First-Served)
- [cite_start]**Source:** Slide 6.11 
- **Mechanism:** Non-preemptive. Processes are executed in the order of arrival.
- [cite_start]**Problem:** Suffers from the *Convoy Effect* where short processes wait for long ones[cite: 148].

### 2. SJF (Shortest Job First)
- [cite_start]**Source:** Slide 6.13 [cite: 169]
- **Mechanism:** Associates each process with the length of its next CPU burst. The shortest one is selected.
- [cite_start]**Advantage:** Provably optimal for minimizing average waiting time.

### 3. Round Robin (RR)
- [cite_start]**Source:** Slide 6.21 [cite: 323]
- **Mechanism:** Preemptive. [cite_start]Each process gets a small unit of CPU time (*Time Quantum*)[cite: 324].
- [cite_start]**Use Case:** Designed specifically for time-sharing systems[cite: 339].

## Compilation
Since these are simulations and do not use OS-specific threads, they can be compiled simply:
```bash
gcc fcfs.c -o fcfs
gcc sjf.c -o sjf
gcc round_robin.c -o round_robin