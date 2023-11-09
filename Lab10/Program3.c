// L Devansh CS21B2023

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdint.h> // Include this for intptr_t

sem_t rd, wrt;
int rcount = 0;

void *reader(void *param);
void *writer(void *param);

int main() {
    pthread_t tid[6];
    int i;

    sem_init(&rd, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_create(&tid[0], NULL, writer, (void *)(intptr_t)1); // Create the writer thread with ID 1

    for (i = 1; i < 6; i++) {
        pthread_create(&tid[i], NULL, reader, (void *)(intptr_t)i); // Create 5 reader threads
    }

    for (i = 0; i < 6; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}

void *reader(void *param) {
    int i;
    int id = (int)(intptr_t)param;
    for (i = 0; i < 10; i++) {
        sem_wait(&rd);
        rcount++;
        if (rcount == 1) {
            sem_wait(&wrt);
        }
        sem_post(&rd);
        printf("Reader %d is reading\n", id);
        sem_wait(&rd);
        rcount--;
        if (rcount == 0) {
            sem_post(&wrt);
        }
        sem_post(&rd);
    }
    pthread_exit(0);
}

void *writer(void *param) {
    int i;
    int id = (int)(intptr_t)param;
    for (i = 0; i < 10; i++) {
        sem_wait(&wrt);
        printf("Writer %d is writing\n", id);
        sem_post(&wrt);
    }
    pthread_exit(0);
}
