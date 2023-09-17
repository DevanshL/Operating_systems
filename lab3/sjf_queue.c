// cs21b2023
// Devansh Lingamaneni
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

struct sjf {
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
};

struct minheap {
    struct sjf* process;
    struct minheap* next;
};

struct Queue {
    struct minheap* front;
    struct minheap* rear;
};

struct minheap* createnode(struct sjf* process) {
    struct minheap* node = (struct minheap*)malloc(sizeof(struct minheap));
    node->process = process;
    node->next = NULL;
    return node;
}

void enqueue(struct Queue* queue, struct sjf* process) {
    struct minheap* newnode = createnode(process);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newnode;
    } else {
        queue->rear->next = newnode;
        queue->rear = newnode;
    }
}

struct sjf* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    } else {
        struct minheap* temp = queue->front;
        queue->front = queue->front->next;
        if (queue->front == NULL) {
            queue->rear = NULL;
        }
        struct sjf* process = temp->process;
        free(temp);
        return process;
    }
}

void shortestJobFirst(struct sjf* processes, int n) {
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
            enqueue(&queue, &processes[i]);
            i++;
        }

        if (queue.front == NULL) {
            curr_time++;
            continue;
        }

        struct sjf* curr = dequeue(&queue);

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

    struct sjf* processes = (struct sjf*)malloc(n * sizeof(struct sjf));

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
