#include <stdio.h>
#include <stdbool.h>

#define MAX_PARTITIONS 20
#define MAX_PROCESSES 20

// Function to simulate MVT memory management
void simulateMVT(int totalMemory) {
    int memoryUsed = 0;
    int processMemory[MAX_PROCESSES] = {0};
    int processCount = 0;

    printf("\n--- Simulating MVT ---\n");
    while (true) {
        char choice;
        printf("\nDo you want to allocate memory to a process? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'n' || choice == 'N') {
            break;
        }

        int memoryNeeded;
        printf("Enter memory required for the process: ");
        scanf("%d", &memoryNeeded);

        if (memoryUsed + memoryNeeded <= totalMemory) {
            processMemory[processCount++] = memoryNeeded;
            memoryUsed += memoryNeeded;
            printf("Memory allocated. Current memory usage: %d/%d\n", memoryUsed, totalMemory);
        } else {
            printf("Not enough memory available. Allocation failed.\n");
        }
    }

    printf("\nProcesses and their memory usage:\n");
    for (int i = 0; i < processCount; i++) {
        printf("Process %d: %d units\n", i + 1, processMemory[i]);
    }
    printf("Total memory used: %d/%d\n", memoryUsed, totalMemory);
    printf("Free memory: %d\n", totalMemory - memoryUsed);
}

// Function to simulate MFT memory management
void simulateMFT(int totalMemory, int partitionSize) {
    int partitions = totalMemory / partitionSize;
    int memoryUsed = 0;
    bool partitionOccupied[MAX_PARTITIONS] = {false};

    printf("\n--- Simulating MFT ---\n");
    while (true) {
        char choice;
        printf("\nDo you want to allocate memory to a process? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'n' || choice == 'N') {
            break;
        }

        int memoryNeeded;
        printf("Enter memory required for the process (must be <= partition size %d): ", partitionSize);
        scanf("%d", &memoryNeeded);

        if (memoryNeeded > partitionSize) {
            printf("Error: Memory needed exceeds partition size. Allocation failed.\n");
            continue;
        }

        bool allocated = false;
        for (int i = 0; i < partitions; i++) {
            if (!partitionOccupied[i]) {
                partitionOccupied[i] = true;
                memoryUsed += partitionSize;
                printf("Memory allocated in partition %d. Current memory usage: %d/%d\n", i + 1, memoryUsed, totalMemory);
                allocated = true;
                break;
            }
        }

        if (!allocated) {
            printf("No free partitions available. Allocation failed.\n");
        }
    }

    printf("\nPartition statuses:\n");
    for (int i = 0; i < partitions; i++) {
        printf("Partition %d: %s\n", i + 1, partitionOccupied[i] ? "Occupied" : "Free");
    }
    printf("Total memory used: %d/%d\n", memoryUsed, totalMemory);
    printf("Free memory: %d\n", totalMemory - memoryUsed);
}

int main() {
    int choice;
    int totalMemory;

    printf("Enter the total memory available: ");
    scanf("%d", &totalMemory);

    while (true) {
        printf("\nChoose a memory management technique:\n");
        printf("1. MVT (Multiprogramming with a Variable Number of Tasks)\n");
        printf("2. MFT (Multiprogramming with a Fixed Number of Tasks)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) {
            break;
        }

        switch (choice) {
            case 1:
                simulateMVT(totalMemory);
                break;
            case 2: {
                int partitionSize;
                printf("Enter the partition size for MFT: ");
                scanf("%d", &partitionSize);
                if (partitionSize > 0) {
                    simulateMFT(totalMemory, partitionSize);
                } else {
                    printf("Partition size must be greater than 0.\n");
                }
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    printf("\nExiting program. Thank you!\n");
    return 0;
}
