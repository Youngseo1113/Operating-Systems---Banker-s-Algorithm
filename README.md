# Operating-Systems---Banker-s-Algorithm# Banker's Algorithm - Safety Check

This C program implements the Banker's Algorithm, specifically the Safety Algorithm, to determine if a given system state is safe or unsafe. If the system is safe, it outputs a possible safe sequence of process execution.

## System State Analyzed

The program analyzes the following system snapshot:

* **Processes:** P0, P1, P2, P3, P4 (5 processes)
* **Resource Types:** A, B, C (3 types)
* **Total Instances:** A=10, B=5, C=7
* **Snapshot at t0:**

    | Process | Allocation (A B C) | Max (A B C) | Available (A B C) |
    | :------ | :----------------- | :---------- | :---------------- |
    | P0      | 0 1 0              | 7 5 3       | 3 3 2             |
    | P1      | 2 0 0              | 3 2 2       |                   |
    | P2      | 3 0 2              | 9 0 2       |                   |
    | P3      | 2 1 1              | 2 2 2       |                   |
    | P4      | 0 0 2              | 4 3 3       |                   |

## Input File Format (`input.txt`)

The program reads the system state from the `input.txt` file. The format is as follows:

1.  **Line 1:** `P R` (Number of processes, Number of resource types)
2.  **Line 2:** `r1 r2 ... rR` (Available instances for each resource type)
3.  **Next P lines:** The Allocation matrix (P rows, R columns), one row per process.
    ```
    alloc_p0_r1 alloc_p0_r2 ... alloc_p0_rR
    alloc_p1_r1 alloc_p1_r2 ... alloc_p1_rR
    ...
    alloc_p(P-1)_r1 ... alloc_p(P-1)_rR
    ```
4.  **Next P lines:** The Max matrix (P rows, R columns), one row per process.
    ```
    max_p0_r1 max_p0_r2 ... max_p0_rR
    max_p1_r1 max_p1_r2 ... max_p1_rR
    ...
    max_p(P-1)_r1 ... max_p(P-1)_rR
    ```

**Example `input.txt`:**

```text
5 3
3 3 2
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
