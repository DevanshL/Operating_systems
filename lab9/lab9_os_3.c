#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Declare two semaphores
sem_t semaphore_a;
sem_t semaphore_b;

void *thread_a(void *x) {
    printf("statement A1\n");
    sleep(1);
    printf("statement A2\n");

    // Signal that A is done
    sem_post(&semaphore_a);

    pthread_exit(NULL);
}

void *thread_b(void *x) {
    // Wait for A to finish
    sem_wait(&semaphore_a);

    printf("statement B1\n");
    sleep(1);
    printf("statement B2\n");
    pthread_exit(NULL);
}

int main() {
    // Initialize the semaphores
    sem_init(&semaphore_a, 0, 0);
    sem_init(&semaphore_b, 0, 0);

    pthread_t t_a, t_b;

    pthread_create(&t_a, NULL, thread_a, NULL);
    pthread_create(&t_b, NULL, thread_b, NULL);

    pthread_join(t_a, NULL);
    pthread_join(t_b, NULL);

    // Destroy the semaphores
    sem_destroy(&semaphore_a);
    sem_destroy(&semaphore_b);

    return 0;
}
