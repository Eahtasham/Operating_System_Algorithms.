#include <stdio.h>
#include <stdlib.h>

// Function to calculate the total seek time using FCFS disk scheduling
int calculateTotalSeekTime(int requests[], int n, int head) {
    int totalSeekTime=0;
    int currentPos=head;
    for(int i=0;i<n;i++){
        int seekTime=abs(currentPos-requests[i]);
        totalSeekTime+= seekTime;
        head=requests[i];
    }
    return totalSeekTime;
}

int main() {
    int n; // Number of disk requests
    int head; // Initial position of the disk head

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    int totalSeekTime = calculateTotalSeekTime(requests, n, head);

    printf("Total seek time using FCFS disk scheduling: %d\n", totalSeekTime);

    return 0;
}
