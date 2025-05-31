# Multi-Threaded Chat Bots with Semaphore Synchronization

## Project Description

This project implements a multi-threaded program where seven concurrent chat bot threads write messages to a shared file (`QUOTE.txt`). The goal is to safely coordinate access to this shared resource using POSIX semaphores to avoid race conditions and data corruption. Each bot runs in its own thread and performs asynchronous writes to the file, adhering to a specific timing pattern and synchronization protocol.

## Project Specifications

- A file named `QUOTE.txt` is created in the current working directory at program startup.
- The program writes the main process ID (PID) followed by a carriage return and newline to `QUOTE.txt`.
- A POSIX semaphore named `FLAG` is created and used to manage exclusive access to the file.
- Seven threads are created using `pthread_create()`. Each thread runs concurrently.
- Threads are categorized as follows:
  - Even-numbered threads (0, 2, 4, 6) perform actions every **2 seconds**.
  - Odd-numbered threads (1, 3, 5) perform actions every **3 seconds**.
- Each thread:
  - Waits to acquire the semaphore `FLAG`.
  - Opens `QUOTE.txt` and writes its thread ID (TID) and a quote, followed by a carriage return and newline.
  - Prints to the console: `Thread <thread id> is running`.
  - Closes the file and releases the semaphore.
  - Repeats this process **8 times** before exiting.
- The main process blocks until all threads complete.
- After all threads finish execution, the semaphore is destroyed.
- A friendly exit message is displayed to the console.

## How to Compile and Run

A `Makefile` is provided to build the project.

```bash
# Navigate to the project directory
cd ~/a1

# Build the executable
make

# Run the program
./bots
```

## 📂 Project Structure

```
a1/
├── bots.c            # Main source file with thread and semaphore logic
├── bots.h            # Header file (function prototypes, includes)
├── Makefile          # Builds the 'bots' executable
├── README.md         # Project documentation
├── QUOTE.txt         # Output file written by bots (created at runtime)
```

## System Calls & APIs Used

- `pthread_create()`, `pthread_join()`
- `sem_init()`, `sem_wait()`, `sem_post()`, `sem_destroy()`
- `fopen()`, `fprintf()`, `fclose()`, `sleep()`
- `getpid()`, `pthread_self()`

## Synchronization Strategy

- A binary semaphore (`FLAG`) is used to enforce mutual exclusion.
- Only one thread may access and write to `QUOTE.txt` at a time.
- This prevents race conditions and ensures consistent, uncorrupted output.

## Requirements Summary

- Must compile and execute cleanly on **edoras** using `gcc` or `g++`.
- Must not use `system()` system call.
- All source code must be well-commented and readable.
- Submission must include:
  - All source files
  - Makefile
  - README.md
  - Zip or tar archive uploaded to Canvas




