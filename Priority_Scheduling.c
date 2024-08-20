#include <stdio.h>
#include <stdlib.h>

/* Process structure to store details of each process */
struct Process {
    int ID;         // Process ID
    int AT;         // Arrival Time
    int BT;         // Burst Time
    int CT;         // Completion Time
    int TAT;        // Turnaround Time
    int WT;         // Waiting Time
    int Start_Time; // Start Time
    int Priority;   // Priority
};

/* Function to swap two processes */
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

/* Function to sort processes by arrival time and priority using bubble sort */
void sortByArrivalTime(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].AT > processes[j + 1].AT) {
                swap(&processes[j], &processes[j + 1]);
            } else if (processes[j].AT == processes[j + 1].AT && processes[j].Priority > processes[j + 1].Priority) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

/* Function to calculate times (CT, TAT, WT) and print the process information */
void timeCalculation(struct Process proc[], int n) {
    int total_WT = 0;
    int total_TAT = 0;
    int currentTime = 0;
    int completed = 0; 

    while(completed<n){
        int index=-1;
        int highestPriority = 10000; //taking a higher value to compare
        for (int i = 0; i < n; i++)
        {
            if(proc[i].CT==-1 && proc[i].AT<=currentTime){
                if(proc[i].Priority<highestPriority){
                    highestPriority=proc[i].Priority;
                    index=i;
                }
                else if(proc[i].Priority==highestPriority && proc[i].AT<proc[index].AT){
                    index=i;
                }

            }
        }

        if(index!=-1){
            proc[index].Start_Time=currentTime;
            proc[index].CT=currentTime+proc[index].BT;
            proc[index].TAT=proc[index].CT-proc[index].AT;
            proc[index].WT =proc[index].TAT-proc[index].BT;  
            
            total_TAT += proc[index].TAT;
            total_WT += proc[index].WT;

            currentTime=proc[index].CT;
            completed++;
        }
        else{
            currentTime++;
        }
        


    }
    

    // Printing the process details
    printf("P\tPriority\tStart_Time\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t%d\t%d\t%d\t%d\n", proc[i].ID, proc[i].Priority, proc[i].Start_Time, proc[i].AT, proc[i].BT, proc[i].CT, proc[i].TAT, proc[i].WT);
    }

    printf("Average TAT= %.2f\n", (float)total_TAT / n);
    printf("Average WT= %.2f\n", (float)total_WT / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process P[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the Arrival Time, Burst Time, and Priority for process %d: ", i + 1);
        scanf("%d %d %d", &P[i].AT, &P[i].BT, &P[i].Priority);
        P[i].ID = i + 1;
        P[i].CT = -1; // Initialize CT to -1 to indicate the process is not yet completed
    }

    sortByArrivalTime(P, n);
    timeCalculation(P, n);

    return 0;
}














