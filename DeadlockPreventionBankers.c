#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 20
#define MAX_RESOURCES 20

// Function to check if a state is safe
bool isSafeState(int processes, int resources, int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES]) {
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
                    // Simulate allocation of resources
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
            return false; // System is not in a safe state
        }
    }

    // If safe, print the safe sequence
    printf("Safe State. Safe Sequence: ");
    for (int i = 0; i < index; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

// Function to request resources
void requestResources(int processes, int resources, int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int process) {
    int request[MAX_RESOURCES];

    // Input resource request
    printf("Enter the resource request for Process P%d: ", process);
    for (int i = 0; i < resources; i++) {
        scanf("%d", &request[i]);
    }

    // Check if request is valid
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process P%d has exceeded its maximum claim.\n", process);
            return;
        }
        if (request[i] > available[i]) {
            printf("Error: Resources are not available for Process P%d's request.\n", process);
            return;
        }
    }

    // Temporarily allocate resources to check safety
    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the state is safe after allocation
    if (isSafeState(processes, resources, available, allocation, need)) {
        printf("Request granted.\n");
    } else {
        // Rollback if not safe
        printf("Request denied to avoid deadlock.\n");
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}

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

    // Input Maximum Matrix
    printf("Enter the Maximum Matrix (%d x %d):\n", processes, resources);
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

    // Main loop for resource requests
    while (true) {
        int process;
        char choice;

        printf("\nDo you want to request resources? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'n' || choice == 'N') {
            break;
        }

        printf("Enter the process number (0 to %d): ", processes - 1);
        scanf("%d", &process);

        if (process < 0 || process >= processes) {
            printf("Invalid process number.\n");
            continue;
        }

        requestResources(processes, resources, available, allocation, need, process);
    }

    return 0;
}
