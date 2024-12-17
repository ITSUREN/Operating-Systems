#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the shared buffer
#define ITEM_NUMBER 7

int buffer[BUFFER_SIZE];  // Shared buffer
int in = 0;              // Index for producer (insertion)
int out = 0;             // Index for consumer (removal)

// Semaphores
sem_t empty;  // Counts empty slots in the buffer
sem_t full;   // Counts filled slots in the buffer
pthread_mutex_t mutex;  // Mutex to ensure mutual exclusion

// Function for producing an item
void *producer(void *arg) {
    int item;
    for (int i = 0; i < ITEM_NUMBER; i++) {  // Produce 10 items
        item = rand() % 100;  // Random item to produce
        sem_wait(&empty);  // Decrement empty slots
        pthread_mutex_lock(&mutex);  // Ensure exclusive access

        // Critical Section: Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced item %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;  // Update the index circularly

        pthread_mutex_unlock(&mutex);  // Release the lock
        sem_post(&full);  // Increment filled slots

        sleep(1);  // Sleep to simulate production time
    }
    pthread_exit(NULL);
}

// Function for consuming an item
void *consumer(void *arg) {
    int item;
    for (int i = 0; i < ITEM_NUMBER; i++) {  // Consume 10 items
        sem_wait(&full);  // Decrement filled slots
        pthread_mutex_lock(&mutex);  // Ensure exclusive access

        // Critical Section: Remove the item from the buffer
        item = buffer[out];
        printf("Consumer consumed item %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;  // Update the index circularly

        pthread_mutex_unlock(&mutex);  // Release the lock
        sem_post(&empty);  // Increment empty slots

        sleep(1);  // Sleep to simulate consumption time
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially, buffer is empty
    sem_init(&full, 0, 0);            // Initially, no slots are filled
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    printf("Starting Producer-Consumer Problem...\n");
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("Producer-Consumer Problem Completed Successfully!\n");
    return 0;
}
