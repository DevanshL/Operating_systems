// L Devansh CS21B2O23
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid1, pid2, pid3, pid4;
   
    pid1 = fork();
   
    if (pid1 == -1)
    {
        printf("Fork failed\n");
        exit(0);
    }
   
    else if (pid1 == 0)
    {                                            // Child 1 process
        printf("Child 1 My id is %d and my parent id is %d\n", getpid(), getppid());
    }
    else
    {
       
        wait(NULL);                                     // Wait for child 1 to complete
       
        pid2 = fork();
       
        if (pid2 == -1)
        {
            printf("Fork failed\n");
            exit(0);
        }
       
        else if (pid2 == 0)
        {                                                       // Child 2 process
            wait(NULL);
            printf("Child 2 My id is %d and my parent id is %d\n", getpid(), getppid());
           
            pid3 = fork();
           
            if (pid3 == -1)
            {
                printf("Fork failed\n");
                exit(0);
            }
            else if (pid3 == 0)
            {
                                                    // Child 3 process
                printf("Child 3 My id is %d and my parent id is %d\n", getpid(), getppid());
            }
            else
            {
                wait(NULL);                     // Wait for child 3 to complete
               
                pid4 = fork();
               
                if (pid4 == -1)
                {
                    printf("Fork failed\n");
                    exit(0);
                }
                else if (pid4 == 0)
                {
                                                     // Child 4 process
                    printf("Child 4 My id is %d and my parent id is %d\n", getpid(), getppid());
                }
                else
                {
                    wait(NULL);                          // Wait for child 4 to complete
                }
            }
        }
        else
        {
            wait(NULL); // Wait for child 2 to complete
            wait(NULL);
            printf("Parent Process my id is %d and my parent id is %d\n", getpid(), getppid());
        }
    }
   
    return 0;
}
