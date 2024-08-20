#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to check if a page is present in memory
bool isPagePresent(int page, int* frame, int frameSize) {
    for (int i = 0; i < frameSize; i++) {
        if (frame[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to find the index of the page to replace using LRU algorithm
int findPageToReplace(int* frame, int frameSize, int* referenceString, int referenceIndex) {
    int leastRecentIndex = referenceIndex;
    int replaceIndex = -1;

    for (int i = 0; i < frameSize; i++) {
        int j;
        for (j = referenceIndex - 1; j >= 0; j--) {
            if (frame[i] == referenceString[j]) {
                if (j < leastRecentIndex) {
                    leastRecentIndex = j;
                    replaceIndex = i;
                }
                break;
            }
        }
        // If frame[i] is not found in the reference string, it means it's the least recently used
        if (j == -1) {
            return i;
        }
    }

    return replaceIndex;
}

// Function to display the current page table
void displayPageTable(int* frame, int frameSize) {
    printf("Page Table: ");
    for (int i = 0; i < frameSize; i++) {
        if (frame[i] == -1) {
            printf("[ ] ");
        } else {
            printf("[%d] ", frame[i]);
        }
    }
    printf("\n");
}

int main() {
    int pageSize, frameSize;

    // Input the size of the reference string (PAGE_SIZE)
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &pageSize);

    // Input the size of the page frame (FRAME_SIZE)
    printf("Enter the size of the page frame: ");
    scanf("%d", &frameSize);

    int referenceString[pageSize];
    int frame[frameSize];  // Page frame
    int faults = 0;        // Page faults counter

    // Input the reference string
    printf("Enter the reference string: ");
    for (int i = 0; i < pageSize; i++) {
        scanf("%d", &referenceString[i]);
    }

    // Initialize frame with -1 indicating no page loaded
    for (int i = 0; i < frameSize; i++) {
        frame[i] = -1;
    }

    // Iterate over the reference string
    for (int i = 0; i < pageSize; i++) {
        printf("\nReference String[%d] = %d\n", i, referenceString[i]);

        // Check if the page is present in memory
        if (!isPagePresent(referenceString[i], frame, frameSize)) {
            faults++; // Page fault occurred

            // Find the index of the page to replace using LRU
            int replaceIndex = findPageToReplace(frame, frameSize, referenceString, i);
            printf("Page fault: Replace page %d with %d\n", frame[replaceIndex], referenceString[i]);

            // Replace the page
            frame[replaceIndex] = referenceString[i];
        } else {
            printf("Page hit\n");
        }

        // Display the current page table
        displayPageTable(frame, frameSize);
    }

    printf("\nTotal Page Faults: %d\n", faults);

    return 0;
}
