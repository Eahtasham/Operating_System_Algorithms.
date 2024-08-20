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

// Function to calculate the total seek time using SCAN disk scheduling
int calculateTotalSeekTime(int requests[], int n, int head, char direction, int lower_limit, int upper_limit) {
    int totalSeekTime = 0;
    int currentPosition = head;
    int idx = 0;

    // Sort the requests array
    sort(requests, n);

    // Find the starting point
    for (int i = 0; i < n; i++) {
        if (requests[i] > head) {
            idx = i;
            break;
        }
    }

    // Service the requests in the given direction
    if (direction == 'r') { // moving towards the upper limit of the disk
        for (int i = idx; i < n; i++) {
            int seekTime = abs(requests[i] - currentPosition);
            totalSeekTime += seekTime;
            printf("%d : %d moves\n", requests[i], seekTime);
            currentPosition = requests[i];
        }
        // Reach the upper limit of the disk
        if (currentPosition != upper_limit) {
            totalSeekTime += abs(upper_limit - currentPosition);
            currentPosition = upper_limit;
        }
        // Reverse direction and service the remaining requests
        for (int i = idx - 1; i >= 0; i--) {
            int seekTime = abs(requests[i] - currentPosition);
            totalSeekTime += seekTime;
            printf("%d : %d moves\n", requests[i], seekTime);
            currentPosition = requests[i];
        }
    } else { // moving towards the lower limit of the disk
        for (int i = idx - 1; i >= 0; i--) {
            int seekTime = abs(requests[i] - currentPosition);
            totalSeekTime += seekTime;
            printf("%d : %d moves\n", requests[i], seekTime);
            currentPosition = requests[i];
        }
        // Reach the lower limit of the disk
        if (currentPosition != lower_limit) {
            totalSeekTime += abs(currentPosition - lower_limit);
            currentPosition = lower_limit;
        }
        // Reverse direction and service the remaining requests
        for (int i = idx; i < n; i++) {
            int seekTime = abs(requests[i] - currentPosition);
            totalSeekTime += seekTime;
            printf("%d : %d moves\n", requests[i], seekTime);
            currentPosition = requests[i];
        }
    }

    return totalSeekTime;
}

int main() {
    int lower_limit, upper_limit;
    int head; // Initial position of the disk head
    char direction; // Initial direction: 'l' for left, 'r' for right
    int n; // Number of disk requests

    printf("Enter the lower and upper limits of the disk: ");
    scanf("%d %d", &lower_limit, &upper_limit);

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

    int totalSeekTime = calculateTotalSeekTime(requests, n, head, direction, lower_limit, upper_limit);

    printf("Total seek time using SCAN disk scheduling: %d\n", totalSeekTime);

    return 0;
}
