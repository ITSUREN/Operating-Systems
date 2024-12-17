#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //posix thread, create and join
#include <unistd.h> //fork, getpid, getppid [Parents]
#include <sys/types.h> //pid_t
#include <sys/wait.h> //wait()

// Function for the thread
void *threadFunction(void *arg)
{
    printf("Thread ID: %ld | Message: Hello from the thread!\n", pthread_self());
    return NULL;
}

int main() {
    // **PROCESS DEMONSTRATION**
    pid_t pid; // Process ID type pid
    printf("### Process and Thread Implementation ###\n\n");

    printf("Creating a new process...\n");
    pid = fork(); // Fork system call to create a child process

    if (pid < 0)
    {
        // Fork failed
        printf("Failed to create a process!\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child Process
        printf("Child Process (PID: %d): Hello from the child process!\n", getpid());
        printf("Child Process: Parent's PID: %d\n", getppid());
    }
    else
    {
        // Parent Process
        printf("Parent Process (PID: %d): Hello from the parent process!\n", getpid());

        // Wait for the child process to complete
        wait(NULL);
        printf("Parent Process: Child process completed.\n\n");
    }

    // **THREAD DEMONSTRATION**
    pthread_t thread; // Thread ID
    printf("Creating a thread...\n");

    // Creating a thread
    if (pthread_create(&thread, NULL, threadFunction, NULL) != 0) {
        printf("Failed to create a thread!\n");
        return 1;
    }

    // Wait for the thread to complete
    pthread_join(thread, NULL);
    printf("Main Program: Thread execution completed.");

    printf("\nProgram completed successfully.\n");
    return 0;
}
