// L. Devansh CS21B2023
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main()
{
    int n;
    
    pid_t pid;
    pid = fork();
    
    if(pid == -1)
    {
        printf("Fork error : \n");
        exit(1);
    }
    
    if(pid == 0)
    {
        printf("CHILD PROCESS \n");
        printf("Enter size of the child array : ");
        scanf("%d",&n);
        
        int *newnode = (int*)malloc(n*sizeof(int));
        printf("Enter the elements : \n");
        for(int i=0;i<n;i++)
        {
            scanf("%d",&newnode[i]);
        }
        
        printf("Array elements and their addresses:\n");
        for (int i = 0; i < n; i++) 
        {
        printf("Element: %d\n", newnode[i]);
        printf("Address: %p\n ",&newnode[i]);
        }
        
        // reverse array and print values
        printf("reverse the array and print its values.\n");
        for(int i=0;i<n/2;i++)
        {
            int temp = newnode[i];
            newnode[i] = newnode[n-i-1];
            newnode[n-i-1] = temp;
        }
        
        printf("The Reversed array is : \n");
        for(int i=0;i<n;i++)
        {
            printf("%d",newnode[i]);
        }
        printf("\n");
        free(newnode);
    }
    
    else
    {
        wait(NULL);
        printf("Parent PROCESS \n");
        printf("Enter size of the parent array : ");
        scanf("%d",&n);
        
        int *newnode = (int*)malloc(n*sizeof(int));
        printf("Enter the elements : \n");
        for(int i=0;i<n;i++)
        {
            scanf("%d",&newnode[i]);
        }
        
        printf("Array elements and their addresses:\n");
        for (int i = 0; i < n; i++) 
        {
        printf("Element: %d\n", newnode[i]);
        printf("Address: %p\n ",&newnode[i]);
        printf("\n");
        }
        
        // sort array and print values
        printf("sorting the array and print its values.\n");
        printf("");
        for(int i=0;i<n-1;i++)
        {
            for(int j=0;j<n-i-1;j++)
            {
                if(newnode[j]>newnode[j+1])
                {
                    int temp1 = newnode[j];
                    newnode[j] = newnode[j+1];
                    newnode[j+1] = temp1;
                }
            }
        }
        
        printf("The sorted array is : \n");
        for(int i=0;i<n;i++)
        {
            printf("%d",newnode[i]);
        }
        printf("\n");
        free(newnode);
    }
    
    return 0;
}