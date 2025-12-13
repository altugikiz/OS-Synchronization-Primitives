# Race Condition Demonstration

This directory contains a practical demonstration of a **Race Condition**, a fundamental concept in Operating Systems Concurrency (Chapter 5).

## 🛑 The Problem

When multiple threads access and manipulate shared data concurrently, the outcome depends on the particular order in which the access takes place. This is called a **Race Condition**.

In `race_condition_demo.c`, two threads increment a shared counter 1,000,000 times each. Theoretically, the result should be 2,000,000. However, in practice, the result is often lower.

## 🔍 Technical Analysis (Why it fails)

As explained in Silberschatz (Slide 5.7), a high-level language statement like `count++` is implemented in machine language as a sequence of operations:

1.  `register1 = count`
2.  `register1 = register1 + 1`
3.  `count = register1`

If the Operating System performs a context switch between step 1 and step 3 (e.g., Thread A loads the value 5, gets interrupted, Thread B loads 5, increments to 6, saves it, then Thread A resumes and saves 6), one increment operation is lost.

## 🛠️ The Solution

To fix this, we need to ensure **Mutual Exclusion** in the Critical Section. This is demonstrated in the `03-Synchronization` directory using:
- Mutex Locks
- Semaphores