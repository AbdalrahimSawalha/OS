# CPU Scheduling Simulator 🖥️

---

## 1. Overview 📘

1. This project implements a CPU Scheduling Simulator using C++.
2. It simulates different scheduling algorithms used in Operating Systems.
3. It reads process data from an input file.
4. It calculates scheduling performance metrics.

---

## 2. Implemented Scheduling Algorithms ⚙️

1. First Come First Serve (FCFS)
   1.1 Executes processes in order of arrival
   1.2 Non-preemptive scheduling

2. Shortest Remaining Time (SRT)
   2.1 Preemptive scheduling algorithm
   2.2 Always executes the process with the shortest remaining burst time

3. Round Robin (RR)
   3.1 Preemptive scheduling algorithm
   3.2 Uses fixed time quantum
   3.3 Cycles through processes fairly

---

## 3. Process Parameters 📋

Each process includes:

1. Process ID
2. Arrival Time
3. Burst Time
4. Completion Time
5. Waiting Time
6. Turnaround Time

---

## 4. Performance Metrics 📊

The simulator calculates:

1. Waiting Time for each process
2. Turnaround Time for each process
3. Average Waiting Time
4. Average Turnaround Time

---

## 5. Input Format 📥

The input file must contain:

1. Number of processes
2. Arrival time and burst time for each process

Example:

```
3
0 5
1 3
2 8
```

---

## 6. Execution ▶️

1. Compile the program:

```
g++ main.cpp -o scheduler
```

2. Run the program:

```
scheduler.exe
```

3. Select scheduling algorithm:

```
1. FCFS
2. SRT
3. RR
4. Exit
```

---

## 7. Technical Concepts 🧠

1. CPU Scheduling Algorithms
2. Preemptive Scheduling
3. Non-preemptive Scheduling
4. Context Switching
5. Process Scheduling Simulation
6. Performance Analysis

---

## 8. Language and Tools 🛠️

1. C++ Programming Language
2. Standard Template Library (STL)
3. File Handling

---

## 9. Author 👨‍💻

Abdalrahim Sawalha

---

## 10. Course 

Operating Systems

---
