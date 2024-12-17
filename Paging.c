#include <stdio.h>

#define MAX_PAGES 100
#define MAX_FRAMES 100

void displayPageTable(int pageTable[], int pages) {
    printf("\nPage Table:\n");
    printf("Page Number\tFrame Number\n");
    for (int i = 0; i < pages; i++) {
        printf("%d\t\t%d\n", i, pageTable[i]);
    }
}

void simulatePaging() {
    int memorySize, pageSize, numPages, numFrames, physicalMemorySize;
    int pageTable[MAX_PAGES];
    int frameOccupied[MAX_FRAMES] = {0}; // Keep track of frame usage

    printf("Enter the size of physical memory (in KB): ");
    scanf("%d", &physicalMemorySize);

    printf("Enter the size of a page/frame (in KB): ");
    scanf("%d", &pageSize);

    // Calculate the number of frames in physical memory
    numFrames = physicalMemorySize / pageSize;

    printf("Enter the size of the process (in KB): ");
    scanf("%d", &memorySize);

    // Calculate the number of pages in the process
    numPages = (memorySize + pageSize - 1) / pageSize; // Round up to the nearest whole page

    if (numPages > numFrames) {
        printf("Error: Process requires more pages (%d) than available frames (%d). Cannot simulate.\n", numPages, numFrames);
        return;
    }

    printf("\nPhysical Memory Size: %d KB\n", physicalMemorySize);
    printf("Page/Frame Size: %d KB\n", pageSize);
    printf("Process Size: %d KB\n", memorySize);
    printf("Number of Pages: %d\n", numPages);
    printf("Number of Frames: %d\n", numFrames);

    // Map pages to frames
    printf("\nEnter the frame numbers to which each page is mapped (0 to %d):\n", numFrames - 1);
    for (int i = 0; i < numPages; i++) {
        printf("Enter the frame number for page %d: ", i);
        scanf("%d", &pageTable[i]);

        if (pageTable[i] < 0 || pageTable[i] >= numFrames) {
            printf("Error: Frame number out of bounds. Try again.\n");
            i--; // Retry the current page
        } else if (frameOccupied[pageTable[i]]) {
            printf("Error: Frame %d is already occupied. Try again.\n", pageTable[i]);
            i--; // Retry the current page
        } else {
            frameOccupied[pageTable[i]] = 1; // Mark frame as occupied
        }
    }

    displayPageTable(pageTable, numPages);

    // Simulate logical to physical address translation
    while (1) {
        int logicalAddress, pageNumber, offset, physicalAddress;

        printf("\nDo you want to translate a logical address? (y/n): ");
        char choice;
        scanf(" %c", &choice);

        if (choice == 'n' || choice == 'N') {
            break;
        }

        printf("Enter a logical address (0 to %d): ", memorySize - 1);
        scanf("%d", &logicalAddress);

        if (logicalAddress < 0 || logicalAddress >= memorySize) {
            printf("Error: Logical address out of bounds.\n");
            continue;
        }

        // Calculate page number and offset
        pageNumber = logicalAddress / pageSize;
        offset = logicalAddress % pageSize;

        // Translate to physical address
        physicalAddress = pageTable[pageNumber] * pageSize + offset;

        printf("Logical Address: %d -> Physical Address: %d\n", logicalAddress, physicalAddress);
    }
}

int main() {
    printf("Paging Technique Simulation\n");
    simulatePaging();
    return 0;
}
