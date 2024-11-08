#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// Function to check if a page is already in a frame
bool isPageInFrames(int page, int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) return true;
    }
    return false;
}

// FIFO Page Replacement
int fifoPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES], pageFaults = 0;
    int index = 0;  // Next frame to replace

    for (int i = 0; i < numFrames; i++) frames[i] = -1;  // Initialize frames

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrames(pages[i], frames, numFrames)) {
            frames[index] = pages[i];
            index = (index + 1) % numFrames;
            pageFaults++;
        }
    }

    return pageFaults;
}

// LRU Page Replacement
int lruPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES], pageFaults = 0;
    int counter[MAX_FRAMES] = {0};  // Keeps track of when each page was last used

    for (int i = 0; i < numFrames; i++) frames[i] = -1;  // Initialize frames

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrames(pages[i], frames, numFrames)) {
            int lruIndex = 0;
            for (int j = 1; j < numFrames; j++) {
                if (frames[j] == -1 || counter[j] < counter[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = pages[i];
            pageFaults++;
        }
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] != -1) counter[j]++;
            if (frames[j] == pages[i]) counter[j] = 0;  // Reset counter for used page
        }
    }

    return pageFaults;
}

// Optimal Page Replacement
int optimalPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES], pageFaults = 0;

    for (int i = 0; i < numFrames; i++) frames[i] = -1;  // Initialize frames

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrames(pages[i], frames, numFrames)) {
            int replaceIndex = -1, farthestDistance = -1;
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
                int k;
                for (k = i + 1; k < numPages; k++) {
                    if (frames[j] == pages[k]) break;
                }
                if (k > farthestDistance) {
                    farthestDistance = k;
                    replaceIndex = j;
                }
            }
            frames[replaceIndex] = pages[i];
            pageFaults++;
        }
    }

    return pageFaults;
}

// Main function
int main() {
    int numPages, numFrames;
    int pages[MAX_PAGES];

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    printf("Enter the page reference sequence: ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    // Calculate page faults for each algorithm
    int fifoFaults = fifoPageReplacement(pages, numPages, numFrames);
    int lruFaults = lruPageReplacement(pages, numPages, numFrames);
    int optimalFaults = optimalPageReplacement(pages, numPages, numFrames);

    // Display results
    printf("\nPage Replacement Algorithms Results:\n");
    printf("FIFO Page Faults: %d\n", fifoFaults);
    printf("LRU Page Faults: %d\n", lruFaults);
    printf("Optimal Page Faults: %d\n", optimalFaults);

    return 0;
}
