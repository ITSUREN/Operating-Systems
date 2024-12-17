#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100

// Function prototypes
void fifoPageReplacement(int pages[], int n, int frames);
void lruPageReplacement(int pages[], int n, int frames);
void lfuPageReplacement(int pages[], int n, int frames);
void optimalPageReplacement(int pages[], int n, int frames);
void displayFrameState(int frame[], int frames);

int main() {
    int pages[MAX_PAGES], n, frames, choice;

    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    while (1) {
        printf("\nChoose a page replacement algorithm:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. LFU\n");
        printf("4. Optimal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifoPageReplacement(pages, n, frames);
                break;
            case 2:
                lruPageReplacement(pages, n, frames);
                break;
            case 3:
                lfuPageReplacement(pages, n, frames);
                break;
            case 4:
                optimalPageReplacement(pages, n, frames);
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// FIFO Page Replacement
void fifoPageReplacement(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], front = 0, pageFaults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1; // Initialize frames

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[front] = pages[i];
            front = (front + 1) % frames;
            pageFaults++;
        }
        displayFrameState(frame, frames);
    }
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

// LRU Page Replacement
void lruPageReplacement(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], recent[MAX_FRAMES], pageFaults = 0, time = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1; // Initialize frames

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                recent[j] = time++;
                break;
            }
        }
        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < frames; j++) {
                if (recent[j] < recent[lruIndex]) lruIndex = j;
            }
            frame[lruIndex] = pages[i];
            recent[lruIndex] = time++;
            pageFaults++;
        }
        displayFrameState(frame, frames);
    }
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

// LFU Page Replacement
void lfuPageReplacement(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], frequency[MAX_FRAMES], pageFaults = 0;
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        frequency[i] = 0;
    }

    printf("\nLFU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                frequency[j]++;
                break;
            }
        }
        if (!found) {
            int lfuIndex = 0;
            for (int j = 1; j < frames; j++) {
                if (frequency[j] < frequency[lfuIndex] || frame[lfuIndex] == -1) lfuIndex = j;
            }
            frame[lfuIndex] = pages[i];
            frequency[lfuIndex] = 1;
            pageFaults++;
        }
        displayFrameState(frame, frames);
    }
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

// Optimal Page Replacement
void optimalPageReplacement(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], pageFaults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1; // Initialize frames

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int replaceIndex = -1, farthest = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    replaceIndex = j;
                    break;
                }
                int nextUse = -1;
                for (int k = i + 1; k < n; k++) {
                    if (pages[k] == frame[j]) {
                        nextUse = k;
                        break;
                    }
                }
                if (nextUse == -1 || nextUse > farthest) {
                    farthest = nextUse;
                    replaceIndex = j;
                }
            }
            frame[replaceIndex] = pages[i];
            pageFaults++;
        }
        displayFrameState(frame, frames);
    }
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

// Display the current state of frames
void displayFrameState(int frame[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] != -1)
            printf("%d ", frame[i]);
        else
            printf("- ");
    }
    printf("\n");
}
