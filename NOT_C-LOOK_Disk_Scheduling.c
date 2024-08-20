#include <stdio.h>
#include <stdlib.h>

// Function to sort the array
void sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Function to calculate the total seek time using LOOK disk scheduling
int calculateTotalSeekTimeCL(int requests[], int n, int head, char direction) {
    int totalST = 0;
    int currentPos = head;
    int idx = 0;

    // Sort the requests array
    sort(requests, n);
    for(int i=0;i<n;i++){
        if(requests[i]>head){
            idx=i;
            break;
        }
    }

    if(direction=='r'){

        for(int i=idx;i<n;i++){
            int ST=abs(requests[i]-currentPos);
            totalST+= ST;
            printf("%d : %d moves\n", requests[i], ST);
            currentPos=requests[i];
        }

        for(int i=0;i<idx;i++){
            int ST=abs(requests[i]-currentPos);
            totalST+= ST;
            printf("%d : %d moves\n", requests[i], ST);
            currentPos=requests[i];
        }
    }
    else{
        for(int i=idx-1;i>=0;i--){
            int ST=abs(requests[i]-currentPos);
            totalST+= ST;
            printf("%d : %d moves\n", requests[i], ST);
            currentPos=requests[i];
        }
          for(int i=n-1;i>=idx;i--){
            int ST=abs(requests[i]-currentPos);
            totalST+= ST;
            printf("%d : %d moves\n", requests[i], ST);
            currentPos=requests[i];
          }
    }
    return totalST;
    
}
    

int main() {
    int head; // Initial position of the disk head
    char direction; // Initial direction: 'l' for left, 'r' for right
    int n; // Number of disk requests

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the initial direction (l for left, r for right): ");
    scanf(" %c", &direction);

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int totalSeekTime = calculateTotalSeekTimeCL(requests, n, head, direction);

    printf("Total seek time using C-LOOK disk scheduling: %d\n", totalSeekTime);

    return 0;
}
