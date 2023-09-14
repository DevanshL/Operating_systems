// Devansh L CS21B2023
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int a[100];

int maxi(int n)                                                             // maximum element finding
{
    int max = a[0];
    for(int i=1;i<n;i++)
    {
        if(a[i]>max)
        {
            max = a[i];
        }
    }
    return max;
}


int mini(int n)
{
    int mini = a[0];                                                                                // minimum element finding
    for(int i=1;i<n;i++)
    {
        if(a[i]<mini)
        {
            mini = a[i];
        }
    }
    return mini;
}



int main()
{
    int n;
    printf("Enter the element size below 100 : ");
    scanf("%d",&n);
    printf("Enter the array of integers : ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    
    
    pid_t pid;              // declare a variable to store process IDs

    pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    }
    
    if(pid==0)                                      // child created
    {
        printf("\n");       
        printf("Child process \n");
        for(int i=0;i<n;i++)
        {
            a[i] = a[i] + 2;
        }
        
        for(int i=0;i<n;i++)
        {
            printf("the element is %d\n",a[i]);
            printf("Element id is %p\n",&a[i]);
            printf("\n");
        }
        
        int max_ele = maxi(n);
        printf("Maximum element after updation of global array by add of 2 is %d\n",max_ele);
        
        printf("Process id : %d\n",getpid());
        printf("Parent id : %d\n",getppid());
    }
    
    else
    {
        printf("------------------------------------");                 // parent created
          printf("Parent proces : \n");
          for(int i=0;i<n;i++)
          {
            a[i] = a[i] - 3;
          }
        
        for(int i=0;i<n;i++)
          {
            printf("the element is %d\n",a[i]);
            printf("Element id is %p\n",&a[i]);
            printf("\n");
          }
        
        int min_ele = mini(n);
        printf("Minimum element after updation of global array by sub of 3 is %d\n",min_ele);
        printf("Process id : %d\n",getpid());
        printf("Parent id : %d\n",getppid());
        
    }
    return 0;
}