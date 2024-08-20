#include <stdio.h>
#include <stdbool.h>

#define QUEUE_COUNT 3

typedef struct
{
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitTime;
    int turnaroundTime;
    int completionTime;
    int queueLevel;
} Process;

typedef struct
{
    Process *proc[100]; 
    int front;
    int rear;
} Queue;

void enqueue(Queue *queue, Process *p)
{
    if (queue->rear == 100)
        return; 
    queue->proc[queue->rear++] = p;
}

Process *dequeue(Queue *queue)
{
    if (queue->front == queue->rear)
        return NULL; 
    return queue->proc[queue->front++];
}

bool isQueueEmpty(Queue *queue)
{
    return queue->front == queue->rear;
}

void sortProcessesByArrivalTime(Process proc[], int n)
{
    int i, j;
    Process temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (proc[i].arrivalTime > proc[j].arrivalTime)
            {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void calculateCompletionTime(Process proc[], int n, int quantum[], int ganttChart[], int *ganttSize)
{
    int time = 0;
    int completed = 0;
    int i = 0;
    bool isCompleted[n];

    for (i = 0; i < n; i++)
    {
        isCompleted[i] = false;
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].queueLevel = 0; 
    }

    Queue queues[QUEUE_COUNT];
    for (i = 0; i < QUEUE_COUNT; i++)
    {
        queues[i].front = queues[i].rear = 0;
    }

    
    for (i = 0; i < n; i++)
    {
        enqueue(&queues[0], &proc[i]);
    }

    int currentTime = 0;
    int previousPid = -1;

    while (completed != n)
    {
        bool found = false;

        for (i = 0; i < QUEUE_COUNT; i++)
        {
            if (!isQueueEmpty(&queues[i]))
            {
                Process *p = dequeue(&queues[i]);

                if (p->remainingTime <= quantum[i])
                {
                    currentTime += p->remainingTime;
                    p->remainingTime = 0;
                    p->completionTime = currentTime;
                    p->turnaroundTime = p->completionTime - p->arrivalTime;
                    p->waitTime = p->turnaroundTime - p->burstTime;
                    completed++;
                }
                else
                {
                    currentTime += quantum[i];
                    p->remainingTime -= quantum[i];
                    p->queueLevel = (i < QUEUE_COUNT - 1) ? i + 1 : i;
                    enqueue(&queues[p->queueLevel], p);
                }

                if (previousPid != p->pid)
                {
                    ganttChart[*ganttSize] = p->pid;
                    (*ganttSize)++;
                    previousPid = p->pid;
                }
                found = true;
                break;
            }
        }

        if (!found)
        {
            ganttChart[*ganttSize] = -1; 
            (*ganttSize)++;
            currentTime++;
        }
    }
}

void printProcesses(Process proc[], int n)
{
    int i;
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tWait Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].completionTime, proc[i].waitTime, proc[i].turnaroundTime);
    }
}

void calculateAndPrintAverages(Process proc[], int n)
{
    int i;
    float totalWaitTime = 0;
    float totalTurnaroundTime = 0;

    for (i = 0; i < n; i++)
    {
        totalWaitTime += proc[i].waitTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
    }

    printf("Average Wait Time: %.2f\n", totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

void printGanttChart(int ganttChart[], int ganttSize)
{
    int i;
    printf("Gantt Chart:\n|");
    for (i = 0; i < ganttSize; i++)
    {
        if (ganttChart[i] == -1)
        {
            printf(" Idle |");
        }
        else
        {
            printf(" P%d |", ganttChart[i]);
        }
    }
    printf("\n");
}

int main()
{
    int n, i, quantum[QUEUE_COUNT];
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    int ganttChart[100]; 
    int ganttSize = 0;

    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
    }

    for (i = 0; i < QUEUE_COUNT; i++)
    {
        printf("Enter the time quantum for queue %d: ", i + 1);
        scanf("%d", &quantum[i]);
    }

    sortProcessesByArrivalTime(proc, n);
    calculateCompletionTime(proc, n, quantum, ganttChart, &ganttSize);
    printProcesses(proc, n);
    calculateAndPrintAverages(proc, n);
    printGanttChart(ganttChart, ganttSize);

    return 0;
}

