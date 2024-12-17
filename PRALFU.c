#include <stdio.h>
#include <limits.h>
#include "./Modules/PageReplacementModules.c"

#define MAX_FRAMES 100
#define MAX_PAGES 100

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

    lfuPageReplacement(pages, n, frames);
    return 0;
}