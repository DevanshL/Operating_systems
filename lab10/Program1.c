//CS21B2023 DEVANSH L

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


void signal_handling(int signal)
{
    if(signal == SIGFPE) // FLOATING POINT ERROR
    {
        printf("Floating point error \n");
    }
}


int main()
{
    signal(SIGFPE, signal_handling);       // signal creation

    int pid;
    pid = fork();

    if(pid == -1)
    {
        printf("Fork creation failed \n");
        exit(1);
    }
    
    else if(pid == 0)   // child process
    {
        // to print random value btw 10 to 30
        while(1)
        {
            int x = rand()%21+10;
            printf("Child process generated: %d\n",x);
        if (x > 20) {
                printf("Child process exiting...\n");
                exit(0);
            }
        }
            sleep(1);  
    }
    else                   // parent process
    {
        wait(NULL);
        int a[] = {2,1,3,0,5,0,7,9};
        int rem,n;

        printf("Enter the number to be divided by: ");
        scanf("%d",&n);

        for(int i=0;i<8;i++)
        {
            if(a[i]==0)
            {
                raise(SIGFPE);         // raise signal
            }
            else
            {
                rem = a[i]%n;
                printf("Remainder: %d\n",rem);
            }
        }
    }
    return 0;
}