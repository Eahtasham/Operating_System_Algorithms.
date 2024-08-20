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

// Function to find the index of the page to replace using FIFO algorithm
int findPageToReplace(int* frame, int frameSize, int* referenceString, int referenceIndex, int pageSize) {
    // Start from the beginning of the frame
    int replaceIndex = 0;
    bool found = false;

    // Iterate over the reference string from the current index
    for (int i = 0; i < frameSize; i++) {
        found = false;
        for (int j = referenceIndex - 1; j >= 0; j--) {
            if (frame[i] == referenceString[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            replaceIndex = i;
            break;
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

            // Find the index of the page to replace using FIFO
            int replaceIndex = findPageToReplace(frame, frameSize, referenceString, i, pageSize);
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
