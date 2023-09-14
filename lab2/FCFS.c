// Lingamaneni Devansh CS21B2023

#include <stdio.h>
#include <stdlib.h>

struct process{
	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
	int rt;
	struct process *next;
};

struct process *enqueue(struct process *newnode,struct process *rear)
{
	newnode->next = NULL;
    
    if (rear == NULL) {
        return newnode;
    } else {
        rear->next = newnode;
        return newnode;
    }
}

struct process *dequeue(struct process **front)
{
	if(*front == NULL)
	{
		return NULL;
	}
	else
	{
		struct process *temp = *front;
		*front = (*front)->next;
		return temp;
	}
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct process* front = NULL;
    struct process* rear = NULL;
    
     for (int i = 0; i < n; i++) {
        struct process* newnode = (struct process*)malloc(sizeof(struct process));
        printf("Enter details for Process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &newnode->pid);
        printf("Arrival Time: ");
        scanf("%d", &newnode->at);
        printf("Burst Time: ");
        scanf("%d", &newnode->bt);
        
        rear = enqueue( newnode,rear);   
        if (front == NULL) 
        {
            front = rear;
        }
        }
        
        int curr_time = 0;
        struct process *node = (struct process*)malloc(n*sizeof(struct process));
        for(int i=0;i<n;i++)
        {
        	struct process *newnode = dequeue(&front);  // dequeueing first element and store in process
        	if(newnode->at > curr_time)
        	{
        		curr_time = newnode->at;
        	}
        	
        	newnode->ct = curr_time + newnode->bt;
        	newnode->tat = newnode->ct - newnode->at;
        	newnode->wt = newnode->tat - newnode->bt;
        	newnode->rt = newnode->wt; 
        	curr_time = newnode->ct;
        	node[i] = *newnode;
        	free(newnode);
        }
        
        float avg_wt = 0;
        float avg_tat = 0;
        for(int i=0;i<n;i++)
        {
        	avg_wt = avg_wt + node[i].wt;
        	avg_tat = avg_tat + node[i].tat;
        }
        avg_wt = avg_wt/n;
        avg_tat = avg_tat/n;
        printf("Pid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
        for(int i=0;i<n;i++)
        {
        	printf("%d\t%d\t%d\t%d\t%d\t%d\t %d\n",node[i].pid,node[i].at,node[i].bt,node[i].ct,node[i].tat,node[i].wt,node[i].rt);
        }
        
         printf("Avg waiting time: %.2f\n", avg_wt);
    	printf("Avg turnaround time: %.2f\n", avg_tat);
    	 free(node);   
    
	return 0;
}

