ritesh raina
122b1f106


#include <stdio.h>

#define FRAME_COUNT 3

void fifoPageReplacement(int pages[], int n) {
    int frames[FRAME_COUNT];
    int index = 0;
    int pageFaults = 0;

    for (int i = 0; i < FRAME_COUNT; i++) {
        frames[i] = -1;
    }

    printf("FIFO Pages\tFrames\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < FRAME_COUNT; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            frames[index] = page;
            index = (index + 1) % FRAME_COUNT;
            pageFaults++;
        }

        printf("%d\t\t", page);
        for (int j = 0; j < FRAME_COUNT; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
    int hits = n - pageFaults;
    printf("Fault Frequency: %.2f%%\n", (float)pageFaults / n * 100);
    printf("Hit Frequency: %.2f%%\n", (float)hits / n * 100);
}

void lrcPageReplacement(int pages[], int n) {
    int frames[FRAME_COUNT];
    int lastUsed[FRAME_COUNT]; // Stores the last use time for each frame
    int pageFaults = 0;

    // Initialize frames to -1 (indicating empty)
    for (int i = 0; i < FRAME_COUNT; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    printf("LRU Pages\tFrames\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < FRAME_COUNT; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                lastUsed[j] = i; // Update the last used time for this page
                break;
            }
        }

        // If the page is not found, we have a page fault
        if (!pageFound) {
            int lruIndex = 0;

            // Find the least recently used page to replace
            for (int j = 1; j < FRAME_COUNT; j++) {
                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j;
                }
            }

            // Replace the LRU page with the new page
            frames[lruIndex] = page;
            lastUsed[lruIndex] = i; // Update last used time for the replaced page
            pageFaults++;
        }

        // Print the current page and frame state
        printf("%d\t\t", page);
        for (int j = 0; j < FRAME_COUNT; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    // Print the final page fault count and hit/miss frequencies
    printf("Total Page Faults (LRU): %d\n", pageFaults);
    int hits = n - pageFaults;
    printf("Fault Frequency: %.2f%%\n", (float)pageFaults / n * 100);
    printf("Hit Frequency: %.2f%%\n", (float)hits / n * 100);
}

void optimalPageReplacement(int pages[], int n) {
    int frames[FRAME_COUNT];
    int pageFaults = 0;

    for (int i = 0; i < FRAME_COUNT; i++) {
        frames[i] = -1;
    }

    printf("Optimal Pages\tFrames\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < FRAME_COUNT; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        // If page is not found in frames, replace one
        if (!pageFound) {
            int replaceIndex = -1;
            int farthestIndex = i + 1;

            // Find an empty frame
            for (int j = 0; j < FRAME_COUNT; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            // If no empty frame, find the optimal frame to replace
            if (replaceIndex == -1) {
                for (int j = 0; j < FRAME_COUNT; j++) {
                    int nextUse = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (pages[k] == frames[j]) {
                            nextUse = k;
                            break;
                        }
                    }

                    if (nextUse == -1) { // Page not used again
                        replaceIndex = j;
                        break;
                    } else if (nextUse > farthestIndex) { // Farthest use
                        farthestIndex = nextUse;
                        replaceIndex = j;
                    }
                }
            }

            frames[replaceIndex] = page;
            pageFaults++;
        }

        printf("%d\t\t", page);
        for (int j = 0; j < FRAME_COUNT; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("Total Page Faults (Optimal): %d\n", pageFaults);
    int hits = n - pageFaults;
    printf("Fault Frequency: %.2f%%\n", (float)pageFaults / n * 100);
    printf("Hit Frequency: %.2f%%\n", (float)hits / n * 100);
}

int main() {
    int n, ans, ch;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];

    for (int i = 0; i < n; i++) {
        printf("Enter page value: ");
        scanf("%d", &pages[i]);
    }

    do {
        printf("Enter which algorithm you would like to implement:\n");
        printf("1 - FIFO\n2 - LRU\n3 - Optimal\n");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                fifoPageReplacement(pages, n);
                break;
            case 2:
                lrcPageReplacement(pages, n);
                break;
            case 3:
                optimalPageReplacement(pages, n);
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }

        printf("Do you like to continue? (1 - yes, 0 - no): ");
        scanf("%d", &ans);
    } while (ans == 1);

    return 0;
}

output:
Enter number of pages: 6
Enter page value: 7 2 1 2 5 3
Enter page value: Enter page value: Enter page value: Enter page value: Enter page value: Enter which algorithm you would like to implement:
1 - FIFO
2 - LRU
3 - Optimal
1
FIFO Pages	Frames
7		7 
2		7 2 
1		7 2 1 
2		7 2 1 
5		5 2 1 
3		5 3 1 
Total Page Faults: 5
Fault Frequency: 83.33%
Hit Frequency: 16.67%
Do you like to continue? (1 - yes, 0 - no): 1
Enter which algorithm you would like to implement:
1 - FIFO
2 - LRU
3 - Optimal
2
LRU Pages	Frames
7		7 - - 
2		7 2 - 
1		7 2 1 
2		7 2 1 
5		5 2 1 
3		5 2 3 
Total Page Faults (LRU): 5
Fault Frequency: 83.33%
Hit Frequency: 16.67%
Do you like to continue? (1 - yes, 0 - no): 1
Enter which algorithm you would like to implement:
1 - FIFO
2 - LRU
3 - Optimal
3
Optimal Pages	Frames
7		7 
2		7 2 
1		7 2 1 
2		7 2 1 
5		5 2 1 
3		3 2 1 
Total Page Faults (Optimal): 5
Fault Frequency: 83.33%
Hit Frequency: 16.67%
Do you like to continue? (1 - yes, 0 - no): 0


=== Code Execution Successful ===
