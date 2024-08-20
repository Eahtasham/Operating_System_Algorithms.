#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to find the request with the minimum seek time
int findMinSeekTime(int requests[], bool serviced[], int n, int head) {
    int minSeekTime = 10000;
    int minIndex = -1;

    for (int i = 0; i < n; i++) {
        if (!serviced[i]) {
            int seekTime = abs(requests[i] - head);
            if (seekTime < minSeekTime) {
                minSeekTime = seekTime;
                minIndex = i;
            }
        }
    }
    return minIndex;
}

// Function to calculate the total seek time using SSTF disk scheduling
int calculateTotalSeekTime(int requests[], int n, int head) {
    int totalSeekTime = 0;
    int currentPosition = head;
    bool serviced[n];
    
    for (int i = 0; i < n; i++) {
        serviced[i] = false;
    }

    for (int i = 0; i < n; i++) {
        int minIndex = findMinSeekTime(requests, serviced, n, currentPosition);
        if (minIndex == -1) break; // All requests are serviced

        serviced[minIndex] = true;
        int seekTime = abs(requests[minIndex] - currentPosition);
        totalSeekTime += seekTime;
        printf("%d : %d moves\n", requests[minIndex], seekTime);
        currentPosition = requests[minIndex];
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

    printf("Total seek time using SSTF disk scheduling: %d\n", totalSeekTime);

    return 0;
}
