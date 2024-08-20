#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Process{
	int ID;
	int AT;
	int BT;
	int CT;
	int TAT;
	int WT;
	int Start_Time;
};
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortByArrivalTime(struct Process processes[], int n) {
	int i;
    for (i = 0; i < n - 1; i++) {
    	int j;
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].AT > processes[j + 1].AT) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}
void timeCalculation(struct Process proc[],int n){
	int total_WT=0;
	int total_TAT=0;
	
	proc[0].CT=proc[0].BT;
	proc[0].Start_Time=proc[0].AT;
	//Calculating CT and Start TIme
	int i;
	for(i=1;i<n;i++){
        if(proc[i].AT> proc[i-1].CT){
            proc[i].Start_Time=proc[i].AT;
        }
        else{
		proc[i].Start_Time=proc[i-1].CT;
        }
		proc[i].CT=proc[i-1].CT + proc[i].BT;
	}
	
	//Calculating TAT;
	for(i=0;i<n;i++){
		proc[i].TAT=proc[i].CT - proc[i].AT;
		proc[i].WT=proc[i].TAT - proc[i].BT;
		
		total_WT += proc[i].WT;
		total_TAT += proc[i].TAT;
	}
	
	//printing process;
	
	printf("P\tStart_t AT\tBT\tCT\tTAT\tWT\n");
	for(i=0;i<n;i++){
		printf("%d\t%d(ns)\t%d\t%d\t%d\t%d\t%d\n",proc[i].ID, proc[i].Start_Time, proc[i].AT, proc[i].BT, proc[i].CT,proc[i].TAT, proc[i].WT );
	}
	
	printf("Average TAT= %.2f\n", (float)total_TAT/n);
	printf("Average WT= %.2f\n", (float)total_WT/n);
	
	
}
int main() {
	int n;
	printf("Enter the number of processes");
	scanf("%d", &n);
	
	struct Process P[n];
	
	int i;
	for(i=0;i<n;i++){
		printf("Enter the AT and BT for %d ", i+1);
		scanf("%d %d", &P[i].AT, &P[i].BT);
		P[i].ID=i+1;
	}
	
	sortByArrivalTime(P,n);
	timeCalculation(P,n);
	
	
	
	return 0;
}
