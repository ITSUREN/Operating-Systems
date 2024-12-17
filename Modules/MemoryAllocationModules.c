#ifndef STDIO_H
#define STDIO_H
    #include <stdio.h>
#endif

// Modular function to allocate memory using the chosen method
void allocateMemory(int blockSize[], int blocks, int processSize[], int processes, int allocation[], void (*allocationFunc)(int[], int, int[], int, int[])) {
    allocationFunc(blockSize, blocks, processSize, processes, allocation);
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