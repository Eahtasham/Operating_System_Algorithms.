#include <stdio.h>
#include <stdlib.h>

// Function to sort the array
void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to calculate the total seek time using SCAN disk scheduling
int calculateTotalSeekTimeCS(int requests[], int n, int head, int lower_limit, int upper_limit)
{
    int totalSeekTime = 0;
    int currentPosition = head;
    int idx = 0;

    // Sort the requests array
    sort(requests, n);

    // Find the starting point
    for (int i = 0; i < n; i++)
    {
        if (requests[i] > head)
        {
            idx = i;
            break;
        }
    }

    for (int i = idx; i < n; i++)
    {
        int seekTime = abs(requests[i] - currentPosition);
        totalSeekTime += seekTime;
        printf("%d : %d moves\n", requests[i], seekTime);
        currentPosition = requests[i];
    }
    // Reach the upper limit of the disk
    if (currentPosition != upper_limit)
    {
        totalSeekTime += abs(upper_limit - currentPosition);
        printf("%d : move to upper limit\n", upper_limit);
        currentPosition = upper_limit;
    }
    
    totalSeekTime+= abs(currentPosition-lower_limit);
    printf("%d : wrap around to lower limit\n", lower_limit);
    currentPosition=lower_limit;


    // Reverse direction and service the remaining requests
    for (int i = 0; i <idx; i++)
    {
        int seekTime = abs(requests[i] - currentPosition);
        totalSeekTime += seekTime;
        printf("%d : %d moves\n", requests[i], seekTime);
        currentPosition = requests[i];
    }

    return totalSeekTime;
}

int main()
{
    int lower_limit, upper_limit;
    int head; // Initial position of the disk head
    int n;    // Number of disk requests

    printf("Enter the lower and upper limits of the disk: ");
    scanf("%d %d", &lower_limit, &upper_limit);

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests sequence: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    int totalSeekTime = calculateTotalSeekTimeCS(requests, n, head, lower_limit, upper_limit);

    printf("Total seek time using C-SCAN disk scheduling: %d\n", totalSeekTime);

    return 0;
}
