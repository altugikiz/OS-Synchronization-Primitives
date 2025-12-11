# System Concurrency Labs

![Language](https://img.shields.io/badge/language-C-blue.svg)
![Topic](https://img.shields.io/badge/topic-Operating%20Systems-orange.svg)
![Library](https://img.shields.io/badge/library-Pthreads-green.svg)

A comprehensive collection of C programming labs focused on **Operating System Concurrency**, **Multithreading**, and **Process Synchronization**. 

This repository serves as a practical implementation guide for concepts covered in *Operating System Concepts* (Silberschatz, Galvin, and Gagne), specifically **Chapter 4 (Threads)** and **Chapter 5 (Process Synchronization)**.

## 🎯 Objectives

- To demonstrate a deep understanding of **thread lifecycle management** using the POSIX Threads (Pthreads) API.
- To simulate and analyze system-level problems such as **Race Conditions** and **Deadlocks**.
- To implement synchronization primitives including **Mutex Locks**, **Semaphores**, and **Condition Variables**.
- To solve classic synchronization problems (e.g., *Dining Philosophers*, *Producer-Consumer*).

## 📂 Repository Structure

The labs are organized logically by topic:

- **01-Thread-Management/**: Basic thread creation, joining, and parallel execution.
- **02-Race-Conditions/**: Demonstrations of unsynchronized data access and critical section violations.
- **03-Synchronization/**: Solutions using Mutex Locks and Semaphores to ensure data consistency.
- **04-Classic-Problems/**: Implementations of standard OS synchronization challenges.

## 🛠️ Build & Run

### Prerequisites
- GCC Compiler (GNU Compiler Collection)
- Make (Optional, for automated builds)
- Linux/macOS environment (or WSL for Windows)

### Compilation
You can compile individual files using `gcc`. The `-pthread` flag is essential for linking the POSIX thread library.

```bash
# Example: Compiling a basic thread program
gcc -pthread 01-Thread-Management/basic_thread.c -o basic_thread
./basic_thread