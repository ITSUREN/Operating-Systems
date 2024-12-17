#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

// Function prototypes
void firstFit(int blockSize[], int blocks, int processSize[], int processes, int allocation[]);
void bestFit(int blockSize[], int blocks, int processSize[], int processes, int allocation[]);
void worstFit(int blockSize[], int blocks, int processSize[], int processes, int allocation[]);
void allocateMemory(int blockSize[], int blocks, int processSize[], int processes, int allocation[], void (*allocationFunc)(int[], int, int[], int, int[]));
void displayAllocation(int processSize[], int allocation[], int processes);

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int allocation[MAX_PROCESSES]; // Tracks allocation for each process
    int blocks, processes, choice;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the size of each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    while (1) {
        printf("\nChoose the allocation method:\n");
        printf("1. First-Fit\n");
        printf("2. Best-Fit\n");
        printf("3. Worst-Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        for (int i = 0; i < processes; i++) allocation[i] = -1; // Reset allocation

        switch (choice) {
            case 1:
                allocateMemory(blockSize, blocks, processSize, processes, allocation, firstFit);
                break;
            case 2:
                allocateMemory(blockSize, blocks, processSize, processes, allocation, bestFit);
                break;
            case 3:
                allocateMemory(blockSize, blocks, processSize, processes, allocation, worstFit);
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }
        displayAllocation(processSize, allocation, processes);
    }

    return 0;
}

// Modular function to allocate memory using the chosen method
void allocateMemory(int blockSize[], int blocks, int processSize[], int processes, int allocation[], void (*allocationFunc)(int[], int, int[], int, int[])) {
    allocationFunc(blockSize, blocks, processSize, processes, allocation);
}

// First-Fit memory allocation
void firstFit(int blockSize[], int blocks, int processSize[], int processes, int allocation[]) {
    int tempBlockSize[MAX_BLOCKS];
    for (int i = 0; i < blocks; i++) tempBlockSize[i] = blockSize[i]; // Copy block sizes

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (tempBlockSize[j] >= processSize[i]) {
                allocation[i] = j;
                tempBlockSize[j] -= processSize[i];
                break;
            }
        }
    }
}

// Best-Fit memory allocation
void bestFit(int blockSize[], int blocks, int processSize[], int processes, int allocation[]) {
    int tempBlockSize[MAX_BLOCKS];
    for (int i = 0; i < blocks; i++) tempBlockSize[i] = blockSize[i]; // Copy block sizes

    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (tempBlockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || tempBlockSize[j] < tempBlockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            tempBlockSize[bestIdx] -= processSize[i];
        }
    }
}

// Worst-Fit memory allocation
void worstFit(int blockSize[], int blocks, int processSize[], int processes, int allocation[]) {
    int tempBlockSize[MAX_BLOCKS];
    for (int i = 0; i < blocks; i++) tempBlockSize[i] = blockSize[i]; // Copy block sizes

    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (tempBlockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || tempBlockSize[j] > tempBlockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            tempBlockSize[worstIdx] -= processSize[i];
        }
    }
}

// Display memory allocation
void displayAllocation(int processSize[], int allocation[], int processes) {
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}
