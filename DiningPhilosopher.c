#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5  // Number of philosophers
#define NUM_MEALS 3         // Number of meals each philosopher eats

typedef enum { THINKING, HUNGRY, EATING } State;

pthread_mutex_t mutex;                // Mutex for critical section
sem_t sem[NUM_PHILOSOPHERS];          // Semaphores for each philosopher
State state[NUM_PHILOSOPHERS];        // States of philosophers

void test(int philosopher_id) {
    int left = (philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS;
    int right = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    if (state[philosopher_id] == HUNGRY &&
        state[left] != EATING &&
        state[right] != EATING) {
        state[philosopher_id] = EATING;
        printf("Philosopher %d picks up forks %d and %d and starts EATING.\n", 
               philosopher_id, philosopher_id, right);
        sem_post(&sem[philosopher_id]);  // Wake up the hungry philosopher
    }
}

void take_forks(int philosopher_id) {
    pthread_mutex_lock(&mutex);  // Enter critical section

    state[philosopher_id] = HUNGRY;
    printf("Philosopher %d is HUNGRY.\n", philosopher_id);
    test(philosopher_id);  // Try to acquire forks

    pthread_mutex_unlock(&mutex);  // Exit critical section

    sem_wait(&sem[philosopher_id]);  // Wait if forks are not acquired
}

void put_forks(int philosopher_id) {
    int left = (philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS;
    int right = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    pthread_mutex_lock(&mutex);  // Enter critical section

    state[philosopher_id] = THINKING;
    printf("Philosopher %d puts down forks %d and %d and starts THINKING.\n", 
           philosopher_id, philosopher_id, right);

    test(left);   // Check if left neighbor can eat
    test(right);  // Check if right neighbor can eat

    pthread_mutex_unlock(&mutex);  // Exit critical section
}

void *philosopher(void *num) {
    int philosopher_id = *(int *)num;

    for (int i = 0; i < NUM_MEALS; i++) {
        printf("Philosopher %d is THINKING.\n", philosopher_id);
        sleep(1);  // Simulate thinking time

        take_forks(philosopher_id);

        printf("Philosopher %d is EATING (meal %d).\n", philosopher_id, i + 1);
        sleep(2);  // Simulate eating time

        put_forks(philosopher_id);
    }

    printf("Philosopher %d has FINISHED eating.\n", philosopher_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&sem[i], 0, 0);
        state[i] = THINKING;
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&sem[i]);
    }

    printf("Dining Philosophers Simulation Completed Successfully.\n");
    return 0;
}
