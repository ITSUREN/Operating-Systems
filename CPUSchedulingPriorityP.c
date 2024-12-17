#include <stdio.h>
#include <limits.h> // For INT_MAX

struct Process {
    int id;          // Process ID
    int at;          // Arrival Time
    int bt;          // Burst Time
    int remaining_bt; // Remaining Burst Time
    int priority;    // Priority (lower value = higher priority)
    int ct;          // Completion Time
    int tat;         // Turnaround Time
    int wt;          // Waiting Time
};

int main() {
    int n, i, completed = 0, currentTime = 0, prev = -1;
    float totalWT = 0, totalTAT = 0;

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
        printf("Enter Priority for Process P%d (lower value = higher priority): ", p[i].id);
        scanf("%d", &p[i].priority);
        p[i].remaining_bt = p[i].bt; // Initialize remaining burst time
        p[i].ct = 0;
    }

    int executed[n]; // To check if process has been executed once
    for (i = 0; i < n; i++) executed[i] = 0;

    while (completed < n) {
        int index = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority (lower value) that has arrived
        for (i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].remaining_bt > 0 && p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
                index = i;
            }
        }

        if (index == -1) {
            // If no process is available, increment time
            currentTime++;
        } else {
            // Execute the selected process for 1 time unit
            if (!executed[index]) {
                executed[index] = 1;
            }

            p[index].remaining_bt--;
            currentTime++;

            // If the process finishes execution
            if (p[index].remaining_bt == 0) {
                completed++;
                p[index].ct = currentTime;                  // Completion Time
                p[index].tat = p[index].ct - p[index].at;  // Turnaround Time
                p[index].wt = p[index].tat - p[index].bt;  // Waiting Time

                totalWT += p[index].wt;
                totalTAT += p[index].tat;
            }
        }
    }

    // Print Process Details
    printf("\nPROCESS\tARRIVAL TIME\tBURST TIME\tPRIORITY\tCOMPLETION TIME\tTURNAROUND TIME\tWAITING TIME\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }

    // Print Averages
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
