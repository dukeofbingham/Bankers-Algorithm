**Bankers Algorithm**


**Program Description**

This project implements the Banker's Algorithm for deadlock avoidance in resource allocation systems. It determines whether a given system state is safe and, if so, provides a safe sequence for process execution.

**Features**

- Reads system state from a file
- Determines if the system is in a safe state
- Provides a safe sequence of process execution if the state is safe
- Handles multiple resources and processes
- Includes error checking and validation

**FIle Structure** 

- balgorithm.c: Main C program implementing the Banker's Algorithm
- data.txt: Input file containing system state information


**How it Works** 

Inputs:


- Number of processes (n) and resources (m).
- Allocation matrix (resources currently allocated to each process).
- Max matrix (maximum resources each process may need).
- Available resources (resources currently free for allocation).


Safety Check:


The program computes the Need matrix:

    Need[i][j] = Max[i][j] - Allocation[i][j]

**Outputs**


If the system is safe, the program outputs:

    The system is in a safe state.
    Safe sequence: P1 -> P3 -> P0 -> P2 -> P4

    
If the system is unsafe:
      
      The system is not in a safe state.


**Complining**

    gcc balgorithm.c -o balgorithm
    ./balgorithm





**Screenshot**


![Screenshot 2024-11-20 at 1 06 31 PM](https://github.com/user-attachments/assets/5478b8e7-9994-4526-ad41-ef1a40f4d3e5)


<img width="591" alt="Screenshot 2024-11-20 at 4 29 05 PM" src="https://github.com/user-attachments/assets/e150ce76-e844-4585-8f4f-e215781db186">





