#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 20
#define MAX_RESOURCES 20

// Function to check if the system is in a safe state
bool isSafeState(int processes, int resources, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES]) {
    int work[MAX_RESOURCES], finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES], index = 0;

    // Initialize work as available
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    while (true) {
        bool found = false;

        for (int p = 0; p < processes; p++) {
            if (!finish[p]) {
                // Check if need[p][j] <= work[j] for all resources
                bool canAllocate = true;
                for (int j = 0; j < resources; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    // Allocate resources to process p
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[p][j];
                    }
                    safeSequence[index++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }

        // If no process can proceed, break the loop
        if (!found) {
            break;
        }
    }

    // Check if all processes are finished
    for (int p = 0; p < processes; p++) {
        if (!finish[p]) {
            printf("The system is NOT in a safe state.\n");
            return false;
        }
    }

    // Print the safe sequence
    printf("The system is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < index; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

// Main function
int main() {
    int processes, resources;
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resource types: ");
    scanf("%d", &resources);

    // Input Allocation Matrix
    printf("Enter the Allocation Matrix (%d x %d):\n", processes, resources);
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Maximum Requirement Matrix
    printf("Enter the Maximum Requirement Matrix (%d x %d):\n", processes, resources);
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("Enter the Available Resources (%d):\n", resources);
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate Need Matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Print Matrices
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nMaximum Requirement Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check for safe state
    isSafeState(processes, resources, available, max, allocation, need);

    return 0;
}
