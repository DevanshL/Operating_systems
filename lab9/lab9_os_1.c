// Devansh L   CS21B2023

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#define n_thread 5                    // Given
#define values 1000
#define value_per_thread (values/n_thread)                      // For each thread distribution of values

struct threaddata{
    int id;
    int sum;
    int start;
    int end;
};

int total = 0;                                      // global value for total of numbers

void *cal_sum(void *x)
{
    struct threaddata *t_data = x;
    t_data->sum = 0;
    for(int i=t_data->start;i<=t_data->end;i++)
    {
        t_data->sum += i;                    // sum for particular thread
    }
    printf("Thread %d is from %d to %d : Sum = %d\n", t_data->id,t_data->start,t_data->end,t_data->sum);
    pthread_exit(NULL);          // No return of value so exit with NULL.
}

int main()
{
    pthread_t thread[n_thread];
    struct threaddata x[n_thread]; 
    int sum=0;

    // Create and start the threads

    for(int i=0;i<5;i++)
    {
        x[i].id = i+1;
        x[i].start = (i*value_per_thread) + 1;           // starting of thread values   ex : 1
        x[i].end = (i+1)* value_per_thread;              // end of thread values   ex : 200
        if( pthread_create(&thread[i],NULL,cal_sum,&x[i])!=0)
        {
            printf("Thread creation failed\n");
            exit(1);
        }
    }


    // Wait for all threads to complete

    for (int i = 0; i < 5; i++) {
        pthread_join(thread[i], NULL);
        total += x[i].sum;
    }

    printf("The sum of the first 1000 numbers is: %d\n", total);


    return 0;
}