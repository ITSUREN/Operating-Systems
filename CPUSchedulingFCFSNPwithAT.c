#include <stdio.h>

struct Process {
    int id;          // Process ID
    int bt;          // Burst Time
    int at;          // Arrival Time
    int ct;          // Completion Time
    int wt;          // Waiting Time
    int tat;         // Turnaround Time
};

void sortByArrivalTime(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    float wtavg = 0, tatavg = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input Arrival Time and Burst Time
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter Arrival Time for Process P%d: ", p[i].id);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for Process P%d: ", p[i].id);
        scanf("%d", &p[i].bt);
    }

    // Sort processes by Arrival Time
    sortByArrivalTime(p, n);

    // Calculate Completion Time, Turnaround Time, and Waiting Time
    int currentTime = 0;
    for (i = 0; i < n; i++) {
        // If CPU is idle, move to the arrival time of the next process
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }
        p[i].ct = currentTime + p[i].bt;      // Completion Time = Current Time + Burst Time
        p[i].tat = p[i].ct - p[i].at;         // Turnaround Time = Completion Time - Arrival Time
        p[i].wt = p[i].tat - p[i].bt;         // Waiting Time = Turnaround Time - Burst Time
        currentTime = p[i].ct;                // Update current time
        wtavg += p[i].wt;
        tatavg += p[i].tat;
    }

    // Print Process Details
    printf("\nPROCESS\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\tTURNAROUND TIME\tWAITING TIME\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // Print Averages
    printf("\nAverage Waiting Time: %.2f", wtavg / n);
    printf("\nAverage Turnaround Time: %.2f\n", tatavg / n);

    return 0;
}
