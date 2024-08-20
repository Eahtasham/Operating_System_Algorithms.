#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitTime;
    int turnaroundTime;
    int completionTime;
} Process;

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

void calculateCompletionTime(Process proc[], int n, int quantum, int ganttChart[], int *ganttSize)
{
    int time = 0;
    int completed = 0;
    int i = 0;
    bool isCompleted[n];

    for (i = 0; i < n; i++)
    {
        isCompleted[i] = false;
        proc[i].remainingTime = proc[i].burstTime;
    }

    int currentTime = 0;
    int previousPid = -1;

    while (completed != n)
    {
        bool found = false;
        for (i = 0; i < n; i++)
        {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0)
            {
                found = true;
                if (proc[i].remainingTime <= quantum)
                {
                    currentTime += proc[i].remainingTime;
                    proc[i].remainingTime = 0;
                    proc[i].completionTime = currentTime;
                    proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
                    proc[i].waitTime = proc[i].turnaroundTime - proc[i].burstTime;
                    completed++;
                }
                else
                {
                    currentTime += quantum;
                    proc[i].remainingTime -= quantum;
                }

                if (previousPid != proc[i].pid)
                {
                    ganttChart[*ganttSize] = proc[i].pid;
                    (*ganttSize)++;
                    previousPid = proc[i].pid;
                }
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
    int n, i, quantum;
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

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    sortProcessesByArrivalTime(proc, n);
    calculateCompletionTime(proc, n, quantum, ganttChart, &ganttSize);
    printProcesses(proc, n);
    calculateAndPrintAverages(proc, n);
    printGanttChart(ganttChart, ganttSize);

    return 0;
}

