// L Devansh CS21B2023

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define num_res 4
#define num_process 6

// available array
int available[num_res] = {3,3,2,2};

//  max matrix 
int max_mat[num_process][num_res] =
{
    {7, 5, 3, 2},
    {3, 2, 2, 2},
    {9, 0, 2, 2},
    {2, 2, 2, 2},
    {4, 3, 3, 3},
    {5, 5, 2, 0}
};

// allocation matrix
int allocation[num_process][num_res] =
{
    {0, 1, 0, 0},
    {2, 0, 0, 1},
    {3, 0, 2, 2},
    {2, 1, 1, 2},
    {0, 0, 2, 1},
    {0, 1, 2, 0}
};

int safe_seq[num_process];   // safe sequence of processes

// need matrix calculation

void need_mat(int need[num_process][num_res])
{
    for(int i=0;i<num_process;i++)
    {
        for(int j=0;j<num_res;j++)
        {
            need[i][j] = max_mat[i][j] - allocation[i][j];
        }
    }
}

int safe(int req_process,int req[num_res],int need[num_process][num_res])
{
    // use available rescources to work
    int work[num_res];
    // if need<=work doesnt satisfy allocate those process to finish
    int finish[num_process];
    
    for(int i=0;i<num_res;i++)
    {
        work[i] = available[i];
    }
    
    // make finish, false at start for all processes
    for(int i=0;i<num_process;i++)
    {
        finish[i] = 0;  // false
    }
    
    for(int i=0;i<num_res;i++)
    {
        // if request rescource > need_matrix or available_rescource array
        if(req[i]>need[req_process][i] || req[i]>available[i])
        return 0;
    }
    
    for(int i=0;i<num_res;i++)
    {
        available[i] -= req[i];
        allocation[req_process][i] += req[i];
        need[req_process][i] -= req[i]; 
    }
    
    int c=0;
    
    // if need<=work  ------------ work = work+allocation
    while(c<num_process)
    {
        int found = 0;        // make false 
        for(int i=0;i<num_process;i++)
        {
            if(finish[i]==0)
            {   
                int j;
                for(j=0;j<num_res;j++)
                {
                    if(need[i][j]>work[j])
                    break;
                    
                }
                if(j == num_res)
                {
                    for(int k=0;k<num_res;k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    safe_seq[c++] = i;
                    finish[i] = 1; // true
                    found = 1;
                }
            }
        }
        
        if(!found)     // if no process granted then it is unsafe state
        return 0;
    }
    return 1;
}

int main()
{
    int req_process;
    int req[num_res];  // storing request process rescources
    int need[num_process][num_res];
    
    need_mat(need);
    
    printf("Enter any Process number from 0 to 5 for additional request: ");
    scanf("%d",&req_process);
    
    printf("Enter rescource values for particular request : \n");
    for(int i=0;i<num_res;i++)
    {
        scanf("%d",&req[i]);
    }
    
    // check whether rescources given leads to safe state or not
    
    if(safe(req_process,req,need))
    {
     printf("SAFE\n");
     printf("The sequence is \n");
     for(int i=0;i<num_process;i++)
     {
         if(i == num_process-1)
         {
             printf("P%d\n",safe_seq[i]);
         }
         else
         {
             printf("P%d ->",safe_seq[i]);
         }
     }
    }
    else
    {
        printf("UNSAFE\n");
    }
    return 0;
}