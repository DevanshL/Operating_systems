// L.DEVANSH CS21B2023

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define MAX_PHILOSOPHERS 5

pthread_t p[MAX_PHILOSOPHERS];
sem_t forks[MAX_PHILOSOPHERS];

void handle_sigint(int sig) {
    printf("Received Ctrl+C. Exiting...\n");
    exit(0);
}

void *philosopher(void *id) {
    int p_id = *(int *)id;
    int l = p_id;
    int r = (p_id + 1) % MAX_PHILOSOPHERS;
    while (1) {
        printf("Philosopher %d is thinking.\n", p_id);
        sleep(1); // Adjust the thinking time

        // Pick up the left fork
        sem_wait(&forks[l]);
        printf("Philosopher %d picked up the left fork.\n", p_id);

        // Try to pick up the right fork (non-blocking)
        if (sem_trywait(&forks[r]) == 0) {
            // If both forks are available, eat
            printf("Philosopher %d picked up the right fork.\n", p_id);
            printf("Philosopher %d is eating.\n", p_id);
            sleep(5); // Adjust the eating time
            sem_post(&forks[r]); // Release the right fork
            printf("Philosopher %d released the right fork.\n", p_id);
        }

        // Release the left fork
        sem_post(&forks[l]);
        printf("Philosopher %d released the left fork.\n", p_id);
    }
}

int main() {
    int ids[MAX_PHILOSOPHERS];
    
     //  signal handler for Ctrl+C (SIGINT)
    signal(SIGINT, handle_sigint);

    
 //   int sem_init(sem_t *sem, int pshared, unsigned value); 
    for (int i = 0; i < MAX_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }
    
    // Creating philosopher threads
    for (int i = 0; i < MAX_PHILOSOPHERS; i++) {
        ids[i] = i+1;
        if (pthread_create(&p[i], NULL, philosopher, &ids[i]) != 0) {
            printf("Error creating thread\n");
            exit(1);
        }
    }

    for (int i = 0; i < MAX_PHILOSOPHERS; i++) {
        pthread_join(p[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < MAX_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    return 0;
}

