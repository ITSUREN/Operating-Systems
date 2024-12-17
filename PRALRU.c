#include <stdio.h>
#include <limits.h>
#include "./Modules/PageReplacementModules.c"

#define MAX_FRAMES 100
#define MAX_PAGES 100

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

    lruPageReplacement(pages, n, frames);
    return 0;
}