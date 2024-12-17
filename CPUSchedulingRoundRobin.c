#include <stdio.h>

struct Process {
    int id;          // Process ID
    int at;          // Arrival Time
    int bt;          // Burst Time
    int remaining_bt; // Remaining Burst Time
    int ct;          // Completion Time
    int tat;         // Turnaround Time
    int wt;          // Waiting Time
};

int main() {
    int n, i, timeQuantum, completed = 0, currentTime = 0;
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

    printf("\nEnter the Time Quantum: ");
    scanf("%d", &timeQuantum);

    int queue[100], front = 0, rear = 0;
    int executed[n]; // Flag to track processes that have been added to the queue
    for (i = 0; i < n; i++) executed[i] = 0;

    // Enqueue processes that have arrived at time 0
    for (i = 0; i < n; i++) {
        if (p[i].at == 0) {
            queue[rear++] = i;
            executed[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            // If queue is empty, increment time to the next process arrival
            int minArrival = 99999;
            for (i = 0; i < n; i++) {
                if (!executed[i] && p[i].at < minArrival) {
                    minArrival = p[i].at;
                }
            }
            currentTime = minArrival;
            for (i = 0; i < n; i++) {
                if (p[i].at == currentTime && !executed[i]) {
                    queue[rear++] = i;
                    executed[i] = 1;
                }
            }
        }

        int index = queue[front++]; // Dequeue a process
        if (p[index].remaining_bt > timeQuantum) {
            // Execute process for the time quantum
            currentTime += timeQuantum;
            p[index].remaining_bt -= timeQuantum;

            // Check for new arrivals during this time
            for (i = 0; i < n; i++) {
                if (!executed[i] && p[i].at <= currentTime) {
                    queue[rear++] = i;
                    executed[i] = 1;
                }
            }

            // Requeue the current process
            queue[rear++] = index;
        } else {
            // Execute process completely
            currentTime += p[index].remaining_bt;
            p[index].remaining_bt = 0;

            p[index].ct = currentTime;                  // Completion Time
            p[index].tat = p[index].ct - p[index].at;  // Turnaround Time
            p[index].wt = p[index].tat - p[index].bt;  // Waiting Time

            totalWT += p[index].wt;
            totalTAT += p[index].tat;
            completed++;

            // Check for new arrivals during this time
            for (i = 0; i < n; i++) {
                if (!executed[i] && p[i].at <= currentTime) {
                    queue[rear++] = i;
                    executed[i] = 1;
                }
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
