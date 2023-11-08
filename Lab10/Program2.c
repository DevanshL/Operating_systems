// CS21B2023 L DEVANSH

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#define n 5

sem_t empty, full; // Semaphores
sem_t mutex_semaphore;
int buffer[n];

int c = 0; // Count of items in the buffer

int produce_item() {
    int r = rand() % 2;
    sleep(r);
    return rand() % 100;
}

void insert_item(int x) {
    buffer[c] = x;
}

void consume_item(int x) {
    int r = rand() % 2;
    sleep(r);
    printf("Consumed item: %d\n", x);
}

int remove_item() {
    int x = buffer[0];
    for (int i = 0; i < c; i++) {
        buffer[i] = buffer[i + 1];
    }
    return x;
}

void *pro() {
    int x;
    do {
        x = produce_item();
        sem_wait(&empty);
        sem_wait(&mutex_semaphore);
        insert_item(x);
        c++;
        printf("Produced item: %d\n", x);
        sem_post(&mutex_semaphore);
        sem_post(&full);
    } while (1);
}

void *con() {
    int x;
    do {
        sem_wait(&full);
        sem_wait(&mutex_semaphore);
        c--;
        x = remove_item();
        sem_post(&mutex_semaphore);
        sem_post(&empty);
        consume_item(x);
    } while (1);
}

int main() {
    srand(time(NULL)); // Initialize the random number generator

    pthread_t pro_t, con_t;
    sem_init(&empty, 0, n);
    sem_init(&full, 0, 0);
    sem_init(&mutex_semaphore, 0, 1);
    pthread_create(&pro_t, NULL, pro, NULL);
    pthread_create(&con_t, NULL, con, NULL);
    pthread_join(pro_t, NULL);
    pthread_join(con_t, NULL);
    return 0;
}