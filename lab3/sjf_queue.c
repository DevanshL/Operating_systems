// cs21b2023
// Devansh Lingamaneni
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

struct process {
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    struct process* next;
};

struct Queue {
    struct process* front;
    struct process* rear;
};

struct process* createnode(int id, int at, int bt) {
    struct process* node = (struct process*)malloc(sizeof(struct process));
    node->id = id;
    node->at = at;
    node->bt = bt;
    node->next = NULL;
    return node;
}

void enqueue(struct Queue* queue, int id, int at, int bt) {
    struct process* newnode = createnode(id, at, bt);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newnode;
    } else {
        queue->rear->next = newnode;
        queue->rear = newnode;
    }
}

struct process* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    } else {
        struct process* temp = queue->front;
        queue->front = queue->front->next;
        if (queue->front == NULL) {
            queue->rear = NULL;
        }
        return temp;
    }
}

void shortestJobFirst(struct process* processes, int n) {
    struct Queue queue;
    queue.front = queue.rear = NULL;

    int curr_time = 0;
    int total_wt = 0;
    int total_tat = 0;

    int completed_processes = 0;
    int i = 0;

    printf(" pid      AT     BT    CT   TAT    WT    RT\n");
    for (; completed_processes < n;) {
        while (i < n && processes[i].at <= curr_time) {
            enqueue(&queue, processes[i].id, processes[i].at, processes[i].bt);
            i++;
        }

        if (queue.front == NULL) {
            curr_time++;
            continue;
        }

        struct process* curr = dequeue(&queue);

        curr->ct = curr_time + curr->bt;
        curr->tat = curr->ct - curr->at;
        curr->wt = curr->tat - curr->bt;
        curr->rt = curr->wt;

        curr_time = curr->ct;
        completed_processes++;

        total_wt += curr->wt;
        total_tat += curr->tat;

        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\t\n", curr->id, curr->at, curr->bt, curr->ct,
               curr->tat, curr->wt, curr->rt);
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;

    printf("\nAverage waiting time: %.4f\n", avg_wt);
    printf("Average turnaround time: %.4f\n", avg_tat);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process* processes = (struct process*)malloc(n * sizeof(struct process));

    for (int i = 0; i < n; i++) {
        int pid, at, bt;
        printf("Process ID %d : ", i + 1);
        scanf("%d", &pid);
        printf("Arrival Time %d : ", i + 1);
        scanf("%d", &at);
        printf("Burst Time %d : ", i + 1);
        scanf("%d", &bt);
        printf("\n");

        processes[i].id = pid;
        processes[i].at = at;
        processes[i].bt = bt;
    }

    shortestJobFirst(processes, n);
    free(processes); // free spacing

    return 0;
}
