// Lingamaneni Devansh CS21B2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fcfs{
  int pid;                  // processor id's
  int at;                   // arrival time
  int bt;                   // burst time
  int ct;                   // completion time or finish time
  int tat;                  // turnaround time
  int wt;                   // waiting time
  int rt;                   // response time
  struct fcfs *next;
};

struct fcfs *working(struct fcfs*head)              // working of fcfs
{
    struct fcfs *temp = head;
    struct fcfs *temp1,*previous;
    int x;
    while(temp!=NULL)
    {
        temp1 = temp;
        x = temp->bt;                   // storing burst time values in x variable
        while(temp1!=NULL)
        {
            temp1->ct = temp1->ct + x;   // adding burst time values for completion time
            temp1 = temp1->next;
        }
        temp = temp->next;
    }
    
    temp = head;                    // bringing temp  to starting state
    
    while(temp!=NULL)
    {
        temp->tat = temp->ct - temp->at;                //  tat = ct- at
        temp->wt = temp->tat - temp->bt;                // wt = tat - bt
        temp = temp->next;
    }
    temp = head;                            // bringing temp  to starting state
    while(temp!=NULL)
    {
        if(temp == head)
        {
            temp->rt = temp->at;                    // arrival time of each processor i.e. left hand start time
            previous = temp;
            temp = temp->next;
        }
        else
        {
            temp->rt = previous->ct;
            previous = temp;
            temp = temp->next;
        }
    }
    return head;
}

int main()
{
    struct fcfs *head = NULL;
    struct fcfs *temp;
    struct fcfs * temp1;
    int p,a,b;
    int ids;
    printf("Enter the number of processors : ");
    scanf("%d",&p);
    for(int i=0;i<p;i++)
    {
        struct fcfs *newnode = (struct fcfs*)malloc(sizeof(struct fcfs));   //Dynamic memory allocation
        printf("Enter pids : \n");
        scanf("%d",&ids);
        newnode->pid = ids;
        printf("enter arrival time and burst time values of %d  : \n",newnode->pid);
        scanf("%d %d",&a,&b);
        newnode->at = a;
        newnode->bt = b;
        // Let s intialize ct,tat,wt,rt as 0 to add or subtract arrival and burst times
        newnode->ct = 0;
        newnode->tat = 0;
        newnode->rt = 0;
        newnode->wt = 0;
        
        if(head == NULL)
        {
            head = newnode;
            temp = head;
        }
        else
        {
            temp->next = newnode;
            temp = newnode;
        }
    }
    
    head = working(head);
    temp1 = head;
    
    while(temp1!=NULL)
    {
        printf("%d at = %d bt = %d ct = %d tat = %d wt = %d rt = %d\n",temp1->pid,temp1->at,temp1->bt,temp1->ct,temp1->tat,temp1->wt,temp1->rt);
        temp1 = temp1->next;
    }
    
    temp = head;
    int total = 0;
    float avg_wt = 0;
    float avg_tat = 0;
    while(temp!=NULL)
    {
        avg_wt = avg_wt + temp->wt;
        avg_tat = avg_tat + temp->tat;
        total = total + 1;
        temp = temp->next;
    }
    avg_wt = avg_wt/total;
    avg_tat = avg_tat/total;
    printf("Average turn around time is : %f\n",avg_wt);     // average turnaround time
    printf("Average waiting time is : %f",avg_tat);         // average waiting time
    
    return 0;
}