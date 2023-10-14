// L Devansh CS21B2023

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#define n 3
                                                // Global arrays
int a[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}};

int b[3][3] = {
    {6, 5, 4},
    {9, 8, 7},
    {3, 2, 1}};

int add[n][n]; // for addition matrix
int sub[n][n]; // for subtraction matrix
int mul[n][n]; // for multiplication matrix

pthread_t a_t, s_t, m_t; // for each matrix each thread.......

//  Addition  for matrix logic
void *mat_add(void *x)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            add[i][j] = a[i][j] + b[i][j];
        }
    }
    pthread_exit(NULL); // No return value
}

//  Subtraction  for matrix logic
void *mat_sub(void *x)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            sub[i][j] = a[i][j] - b[i][j];
        }
    }
    pthread_exit(NULL); // No return value
}

//  Multiplication  for matrix logic
void *mat_mul(void *x)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mul[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                mul[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    pthread_exit(NULL); // No return value
}

int main()
{
    if (pthread_create(&a_t, NULL, mat_add, NULL) != 0 ||
        pthread_create(&s_t, NULL, mat_sub, NULL) != 0 ||
        pthread_create(&m_t, NULL, mat_mul, NULL) != 0)
    {
        printf("Thread creation failed\n");
        exit(1);
    }
    // wait for completion of thread
    pthread_join(a_t, NULL);
    pthread_join(s_t, NULL);
    pthread_join(m_t, NULL);

    // first print global matrices

    printf("Matrix A:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Matrix B:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Addition Matrix :\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", add[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Subtraction Matrix :\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", sub[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Multiplication Matrix :\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", mul[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}