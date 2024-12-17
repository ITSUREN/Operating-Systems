#include <stdio.h>
#include "./Modules/MemoryAllocationModules.c"

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

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

    allocateMemory(blockSize, blocks, processSize, processes, allocation, firstFit);
    displayAllocation(processSize, allocation, processes);

    return 0;
}

