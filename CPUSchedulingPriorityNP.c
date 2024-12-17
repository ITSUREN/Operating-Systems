#include <stdio.h>
#include <limits.h> // For INT_MIN

struct Process {
    int id;          // Process ID
    int at;          // Arrival Time
    int bt;          // Burst Time
    int priority;    // Priority (higher value = higher priority)
    int ct;          // Completion Time
    int tat;         // Turnaround Time
    int wt;          // Waiting Time
    int completed;   // Flag to track completion
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
    int n, completedProcesses = 0, currentTime = 0, i;
    float wtavg = 0, tatavg = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input Arrival Time, Burst Time, and Priority
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter Arrival Time for Process P%d: ", p[i].id);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for Process P%d: ", p[i].id);
        scanf("%d", &p[i].bt);
        printf("Enter Priority for Process P%d (higher value = higher priority): ", p[i].id);
        scanf("%d", &p[i].priority);
        p[i].completed = 0; // Mark all processes as incomplete initially
    }

    // Sort processes by Arrival Time
    sortByArrivalTime(p, n);

    while (completedProcesses < n) {
        int highestPriority = INT_MIN;
        int index = -1;

        // Find the process with the highest priority that has arrived
        for (i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime && p[i].priority > highestPriority) {
                highestPriority = p[i].priority;
                index = i;
            }
        }

        if (index == -1) {
            // No process has arrived, move currentTime to the next arrival time
            currentTime = p[completedProcesses].at;
        } else {
            // Process the selected process
            p[index].ct = currentTime + p[index].bt;  // Completion Time
            p[index].tat = p[index].ct - p[index].at; // Turnaround Time
            p[index].wt = p[index].tat - p[index].bt; // Waiting Time
            currentTime = p[index].ct;                // Update current time
            p[index].completed = 1;                  // Mark process as completed
            completedProcesses++;
            wtavg += p[index].wt;
            tatavg += p[index].tat;
        }
    }

    // Print Process Details
    printf("\nPROCESS\tARRIVAL TIME\tBURST TIME\tPRIORITY\tCOMPLETION TIME\tTURNAROUND TIME\tWAITING TIME\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }

    // Print Averages
    printf("\nAverage Waiting Time: %.2f", wtavg / n);
    printf("\nAverage Turnaround Time: %.2f\n", tatavg / n);

    return 0;
}
