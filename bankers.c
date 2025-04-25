#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // For bool type

int main() {
    int P; // Number of processes
    int R; // Number of resources

    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Read P and R
    if (fscanf(fp, "%d %d", &P, &R) != 2) {
        fprintf(stderr, "Error reading number of processes and resources.\n");
        fclose(fp);
        return 1;
    }

    // --- Data Structures ---
    int available[R];
    int max[P][R];
    int allocation[P][R];
    int need[P][R];
    bool finish[P];
    int safeSequence[P];
    int work[R];

    // --- Read Available Vector ---
    printf("Reading Available Resources: ");
    for (int j = 0; j < R; j++) {
        if (fscanf(fp, "%d", &available[j]) != 1) {
            fprintf(stderr, "\nError reading available vector.\n");
            fclose(fp);
            return 1;
        }
        printf("%d ", available[j]);
        work[j] = available[j]; // Initialize work vector
    }
    printf("\n");


    // --- Read Allocation Matrix ---
    printf("Reading Allocation Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            if (fscanf(fp, "%d", &allocation[i][j]) != 1) {
                fprintf(stderr, "Error reading allocation matrix at P%d, R%d.\n", i, j);
                fclose(fp);
                return 1;
            }
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    // --- Read Max Matrix ---
    printf("Reading Max Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            if (fscanf(fp, "%d", &max[i][j]) != 1) {
                fprintf(stderr, "Error reading max matrix at P%d, R%d.\n", i, j);
                fclose(fp);
                return 1;
            }
            printf("%d ", max[i][j]);
        }
         printf("\n");
    }

    fclose(fp); // Close the file after reading

    // --- Calculate Need Matrix ---
    printf("\nCalculating Need Matrix:\n");
     for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
             printf("%d ", need[i][j]);
        }
         printf("\n");
    }
     printf("\n");

    // --- Safety Algorithm ---
    for (int i = 0; i < P; i++) {
        finish[i] = false; // Initialize all processes as not finished
    }

    int count = 0; // Count of finished processes
    int sequenceIndex = 0;

    // Loop until all processes are finished or no safe process is found
    while (count < P) {
        bool found = false; // Flag to check if a safe process was found in this pass
        for (int i = 0; i < P; i++) {
            // Check if process i is not finished
            if (finish[i] == false) {
                // Check if Need[i] <= Work
                bool can_allocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break; // No need to check further resources for this process
                    }
                }

                // If Need[i] <= Work, allocate resources and finish process i
                if (can_allocate) {
                    // Add allocation resources back to work
                    printf("Process P%d can run. Work: (", i);
                    for(int k=0; k<R; k++) printf("%d%s", work[k], k==R-1 ? "" : ", ");
                    printf(") -> (");
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                         printf("%d%s", work[j], j==R-1 ? "" : ", ");
                    }
                    printf(")\n");


                    finish[i] = true;       // Mark process as finished
                    safeSequence[sequenceIndex++] = i; // Add to safe sequence
                    count++;                // Increment count of finished processes
                    found = true;           // A safe process was found
                    // No break here, continue checking other processes in the same pass
                }
            }
        }

        // If no process could be allocated resources in this pass, the system is unsafe
        if (found == false) {
            break; // Exit the while loop
        }
    } // End of while loop

    // --- Check Final State ---
    printf("\n--- Result ---\n");
    if (count == P) {
        printf("System is in a SAFE state.\n");
        printf("Safe Sequence: < ");
        for (int i = 0; i < P; i++) {
            printf("P%d%s", safeSequence[i], (i == P - 1) ? " " : ", ");
        }
        printf(">\n");
    } else {
        printf("System is in an UNSAFE state.\n");
        printf("%d processes could not finish.\n", P - count);
    }

    return 0; // Success
}