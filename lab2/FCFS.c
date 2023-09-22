// Lingamaneni Devansh CS21B2023

#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    struct process* next;
};

struct process* enqueue(struct process* newnode, struct process* rear) {
    newnode->next = NULL;

    if (rear == NULL) {
        return newnode;
    } else {
        rear->next = newnode;
        return newnode;
    }
}

struct process* dequeue(struct process** front) {
    if (*front == NULL) {
        return NULL;
    } else {
        struct process* temp = *front;
        *front = (*front)->next;
        return temp;
    }
}

int main() {
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

        rear = enqueue(newnode, rear);
        if (front == NULL) {
            front = rear;
        }
    }

    // Corrected FCFS scheduling logic
    int curr_time = 0;
    struct process* node = (struct process*)malloc(n * sizeof(struct process));

    // Sort the processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (node[j].at > node[j + 1].at) {
                // Swap the processes
                struct process temp = node[j];
                node[j] = node[j + 1];
                node[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (node[i].at > curr_time) {
            curr_time = node[i].at;
        }

        node[i].ct = curr_time + node[i].bt;
        node[i].tat = node[i].ct - node[i].at;
        node[i].wt = node[i].tat - node[i].bt;
        node[i].rt = node[i].wt;
        curr_time = node[i].ct;
    }

    float avg_wt = 0;
    float avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt = avg_wt + node[i].wt;
        avg_tat = avg_tat + node[i].tat;
    }
    avg_wt = avg_wt / n;
    avg_tat = avg_tat / n;
    printf("Pid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t %d\n", node[i].pid, node[i].at, node[i].bt, node[i].ct, node[i].tat, node[i].wt, node[i].rt);
    }

    printf("Avg waiting time: %.2f\n", avg_wt);
    printf("Avg turnaround time: %.2f\n", avg_tat);
    free(node);

    return 0;
}
