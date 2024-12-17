#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_REQUESTS 100

// Function prototypes
void fcfs(int requests[], int n, int head);
void scan(int requests[], int n, int head, int direction, int disk_size);
void look(int requests[], int n, int head, int direction);

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int requests[MAX_REQUESTS];
    int n, head, choice, direction, disk_size;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size (max cylinder value for SCAN): ");
    scanf("%d", &disk_size);

    printf("Enter the initial direction (1 for right/up, 0 for left/down): ");
    scanf("%d", &direction);

    while (1) {
        printf("\n==== DISK SCHEDULING ALGORITHMS ====\n");
        printf("1. FCFS\n");
        printf("2. SCAN\n");
        printf("3. LOOK\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(requests, n, head);
                break;
            case 2:
                scan(requests, n, head, direction, disk_size);
                break;
            case 3:
                look(requests, n, head, direction);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// FCFS Disk Scheduling
void fcfs(int requests[], int n, int head) {
    int total_movement = 0;

    printf("FCFS Disk Scheduling Order:\n");
    printf("%d -> ", head);

    for (int i = 0; i < n; i++) {
        total_movement += abs(requests[i] - head);
        head = requests[i];
        printf("%d -> ", head);
    }

    printf("END\n");
    printf("Total Head Movement: %d\n", total_movement);
}

// SCAN Disk Scheduling
void scan(int requests[], int n, int head, int direction, int disk_size) {
    int total_movement = 0, temp[MAX_REQUESTS], size = 0;
    int boundary = (direction == 1) ? disk_size - 1 : 0;

    // Separate requests for left and right of the head
    for (int i = 0; i < n; i++) {
        temp[size++] = requests[i];
    }
    temp[size++] = boundary;

    qsort(temp, size, sizeof(int), compare);

    int index = 0;
    while (index < size && temp[index] < head)
        index++;

    printf("SCAN Disk Scheduling Order:\n");
    printf("%d -> ", head);

    if (direction == 1) { // Moving towards higher cylinders
        for (int i = index; i < size; i++) {
            total_movement += abs(temp[i] - head);
            head = temp[i];
            printf("%d -> ", head);
        }
        for (int i = index - 1; i >= 0; i--) {
            total_movement += abs(temp[i] - head);
            head = temp[i];
            printf("%d -> ", head);
        }
    } else { // Moving towards lower cylinders
        for (int i = index - 1; i >= 0; i--) {
            total_movement += abs(temp[i] - head);
            head = temp[i];
            printf("%d -> ", head);
        }
        for (int i = index; i < size; i++) {
            total_movement += abs(temp[i] - head);
            head = temp[i];
            printf("%d -> ", head);
        }
    }

    printf("END\n");
    printf("Total Head Movement: %d\n", total_movement);
}

// LOOK Disk Scheduling
void look(int requests[], int n, int head, int direction) {
    int total_movement = 0, temp[MAX_REQUESTS], size = 0;

    for (int i = 0; i < n; i++) {
        temp[size++] = requests[i];
    }

    qsort(temp, size, sizeof(int), compare);

    int index = 0;
    while (index < size && temp[index] < head)
        index++;

    printf("LOOK Disk Scheduling Order:\n");
    printf("%d -> ", head);

    if (direction == 1) { // Moving towards higher cylinders
        for (int i = index; i < size; i++) {
            total_movement += abs(temp[i] - head);
            head = temp[i];
            printf("%d -> ", head);
        }
        for (int i = index - 1; i >= 0; i--) {
            total_movement += abs(temp[i] - head);
            head = temp[i];
            printf("%d -> ", head);
        }
    } else { // Moving towards lower cylinders
        for (int i = index - 1; i >= 0; i--) {
            total_movement += abs(temp[i] - head);
            head = temp[i];
            printf("%d -> ", head);
        }
        for (int i = index; i < size; i++) {
            total_movement += abs(temp[i] - head);
            head = temp[i];
            printf("%d -> ", head);
        }
    }

    printf("END\n");
    printf("Total Head Movement: %d\n", total_movement);
}
