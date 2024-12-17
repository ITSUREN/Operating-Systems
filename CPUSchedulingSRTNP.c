#include <stdio.h>
#include <limits.h> // For INT_MAX

struct Process {
    int id;           // Process ID
    int at;           // Arrival Time
    int bt;           // Burst Time
    int remaining_bt; // Remaining Burst Time
    int ct;           // Completion Time
    int tat;          // Turnaround Time
    int wt;           // Waiting Time
};

int main() {
    int n, i, currentTime = 0, completed = 0, shortest = -1, min_bt;
    float totalWT = 0, totalTAT = 0;

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
        p[i].remaining_bt = p[i].bt; // Initialize remaining burst time
        p[i].ct = 0;
    }

    // Loop until all processes are completed
    while (completed < n) {
        min_bt = INT_MAX;
        shortest = -1;

        // Find the process with the shortest remaining burst time that has arrived
        for (i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].remaining_bt > 0 && p[i].remaining_bt < min_bt) {
                min_bt = p[i].remaining_bt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            // If no process is available, increment time
            currentTime++;
        } else {
            // Execute the selected process for 1 unit of time
            p[shortest].remaining_bt--;
            currentTime++;

            // If the process is completed
            if (p[shortest].remaining_bt == 0) {
                completed++;
                p[shortest].ct = currentTime;                  // Completion Time
                p[shortest].tat = p[shortest].ct - p[shortest].at; // Turnaround Time
                p[shortest].wt = p[shortest].tat - p[shortest].bt; // Waiting Time

                totalWT += p[shortest].wt;
                totalTAT += p[shortest].tat;
            }
        }
    }

    // Print Process Details
    printf("\nPROCESS\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\tTURNAROUND TIME\tWAITING TIME\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // Print Averages
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
