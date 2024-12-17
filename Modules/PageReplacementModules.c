#ifndef STDIO_H
#define STDIO_H
    #include <stdio.h>
#endif

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