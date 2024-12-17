#include <stdio.h>
#include "./Modules/MemoryAllocationModules.c"

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

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

    allocateMemory(blockSize, blocks, processSize, processes, allocation, bestFit);
    displayAllocation(processSize, allocation, processes);

    return 0;
}

