// L Devansh CS21B2023

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include<semaphore.h>

sem_t rd,wrt;              //defining semaphores
int rcount=0;             //read count

void *reader(void *param);
void *writer(void *param);


int main(){
    pthread_t tid[5];
    long int i;
    sem_init(&rd,0,1);
    sem_init(&wrt,0,1);
    pthread_create(&tid[0], NULL, &writer, (void*)1);                         //creating 1 writer process
    
    for(i=0;i<5;i++)
    {
        pthread_create(&tid[i], NULL, &reader, (void*)i);                         //creating 5 reader process
    }
    for (i = 0; i < 5; i++)
    {
        pthread_join(tid[i], NULL);
    }
    return 0;
}



void *reader(void *param)                     //reader process
{ 
    int i;
     int id=(long int)param;
    for(i=0;i<10;i++)
    {
        sem_wait(&rd);
        rcount++;
        if(rcount==1)
        {
            sem_wait(&wrt);                                 
        }
        sem_post(&rd);
        printf("Reader %d is reading\n",id);
        sem_wait(&rd);
        rcount--;
        if(rcount==0)
        {
            sem_post(&wrt);
        }
        sem_post(&rd);
    }
    pthread_exit(0);
}

void *writer(void *param)                       //writer process
{
    int i;
    int id=(long int)param;
    for(i=0;i<10;i++)
    {
        sem_wait(&wrt);
        printf("Writer %d is writing\n",id);
        sem_post(&wrt);
    }
    pthread_exit(0);
}