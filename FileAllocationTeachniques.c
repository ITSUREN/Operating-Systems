#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DISK_SIZE 100  // Size of the disk (number of blocks)

// Global Disk Array to simulate disk blocks
int disk[DISK_SIZE];

// Utility function to initialize the disk
void initialize_disk() {
    for (int i = 0; i < DISK_SIZE; i++) {
        disk[i] = -1;  // -1 indicates that the block is free
    }
}

// Utility function to display the disk
void display_disk() {
    printf("Disk Status:\n");
    for (int i = 0; i < DISK_SIZE; i++) {
        printf("%2d ", disk[i]);
    }
    printf("\n");
}

// SEQUENTIAL ALLOCATION
bool sequential_allocation(int file_id, int file_size) {
    int start = -1;
    int free_count = 0;

    // Find a continuous set of free blocks
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i] == -1) {
            free_count++;
            if (free_count == file_size) {
                start = i - file_size + 1;
                break;
            }
        } else {
            free_count = 0;
        }
    }

    if (start == -1) {
        printf("Error: Not enough contiguous space for File %d (size: %d).\n", file_id, file_size);
        return false;
    }

    // Allocate the file
    for (int i = start; i < start + file_size; i++) {
        disk[i] = file_id;
    }

    printf("Sequential Allocation: File %d allocated starting at block %d.\n", file_id, start);
    return true;
}


// INDEXED ALLOCATION
bool indexed_allocation(int file_id, int file_size) {
    int index_block = -1;

    // Find an index block
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i] == -1) {
            index_block = i;
            break;
        }
    }

    if (index_block == -1) {
        printf("Error: No space for index block for File %d.\n", file_id);
        return false;
    }

    // Store file block locations in an array (simulated index block)
    int file_blocks[file_size];
    int count = 0;

    for (int i = 0; i < DISK_SIZE && count < file_size; i++) {
        if (disk[i] == -1) {
            file_blocks[count++] = i;
        }
    }

    if (count < file_size) {
        printf("Error: Not enough space for File %d (size: %d).\n", file_id, file_size);
        return false;
    }

    // Mark the index block and file blocks
    disk[index_block] = file_id;
    for (int i = 0; i < file_size; i++) {
        disk[file_blocks[i]] = file_id;
    }

    printf("Indexed Allocation: File %d allocated. Index Block: %d. Blocks: ", file_id, index_block);
    for (int i = 0; i < file_size; i++) {
        printf("%d ", file_blocks[i]);
    }
    printf("\n");

    return true;
}

// LINKED ALLOCATION
bool linked_allocation(int file_id, int file_size) {
    int start_block = -1;
    int prev_block = -1;

    int count = 0;
    for (int i = 0; i < DISK_SIZE && count < file_size; i++) {
        if (disk[i] == -1) {
            disk[i] = file_id;

            if (start_block == -1) {
                start_block = i;  // Set starting block
            }

            if (prev_block != -1) {
                // Simulate linking by using a simple output
                printf("Block %d -> Block %d\n", prev_block, i);
            }
            prev_block = i;
            count++;
        }
    }

    if (count < file_size) {
        printf("Error: Not enough space for File %d (size: %d).\n", file_id, file_size);
        return false;
    }

    printf("Linked Allocation: File %d allocated starting at Block %d.\n", file_id, start_block);
    return true;
}

// Main Function to Demonstrate All Strategies
int main() {
    int choice, file_id = 1, file_size;
    initialize_disk();

    while (1) {
        printf("\n==== FILE ALLOCATION STRATEGIES ====\n");
        printf("1. Sequential Allocation\n");
        printf("2. Indexed Allocation\n");
        printf("3. Linked Allocation\n");
        printf("4. Display Disk\n");
        printf("5. Initialize Disk\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file size for Sequential Allocation: ");
                scanf("%d", &file_size);
                sequential_allocation(file_id++, file_size);
                break;

            case 2:
                printf("Enter file size for Indexed Allocation: ");
                scanf("%d", &file_size);
                indexed_allocation(file_id++, file_size);
                break;

            case 3:
                printf("Enter file size for Linked Allocation: ");
                scanf("%d", &file_size);
                linked_allocation(file_id++, file_size);
                break;

            case 4:
                display_disk();
                break;

            case 5:
                initialize_disk();
                printf("Disk initialized.\n");
                break;

            case 6:
                printf("Exiting...\n");
                exit(0);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
