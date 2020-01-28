# CPU Scheduling Algorithms

There are two parts to this project, both of which are written in C:

The first part was used as an exercise to test the data sharing ability of threads and processes.

The second part of this project was to perform cpu scheduling operations on a given input file. It will do the following:

1. Create the number of ready queues as stated in the given input file
2. Assign time quantum (provided in the input file) for Round Robin (RR) algorithm
3. Create all the processes for each of the ready queues based on the input file specification
(such as CPU burst time, arrival order etc.)
4. Ready queues will be executed in the order of their queue number (q 1, q 2, etc.)
5. CPU scheduling algorithms FCFS, SJF, and RR will be applied on each ready queue 

Once the execution of all the ready queues is complete,
the program will output all attributes (order of processes selected, individual and average waiting time for each algorithm (FCFS and SJF), and turnaround time for RR)
to the screen and to a text file “cpu_scheduling_output_file.txt”

Symbols used in the above input file: 
-------------------------------------
q: Ready queue
tq: time quantum
Example: 

-------------------------------------
q 1 tq 4 p1 10 p2 5 p3 7 p4 20 p5 17 p6 9 p7 3 p8 11 p9 15 p10 1

Ready Queue 1 has a total of ten processes namely p1, p2, p3, p4, p5, p6, p7, p8, p9, and p10. The sequence of these processes represents their arrival order. For example, p1 arrives first and p10 arrives last in this list of processes. In the "px y" format, y refers to the CPU burst time for px. For preemptive scheduling algorithms such as RR, a time quantum of 4 is assigned to each process.
