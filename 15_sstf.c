#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //for INT_MAX
#include <math.h> // for math fuctions like sqrt,log etc

void sstf(int queue[], int head, int size) {
    int totalSeek = 0;  // Variable to keep track of the total seek distance
    int visited[size];   // Array to keep track of visited requests

    // Initialize the 'visited' array to mark all requests as not visited
    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }

    // Print the initial head position
    printf("SSTF Order: %d", head);
    visited[head] = 1;  // Mark the initial head position as visited

    // SSTF algorithm
    for (int i = 0; i < size - 1; i++) {
        int minDistance = INT_MAX;  // Variable to store the minimum seek distance
        int minIndex = -1;  // Variable to store the index of the request with minimum seek distance

        // Find the request with the minimum seek distance from the current head position
        for (int j = 0; j < size; j++) {
            if (!visited[j]) {
                int distance = abs(queue[j] - head);  // Calculate seek distance
                // If the current request has a smaller seek distance, update minDistance and minIndex
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = j;
                }
            }
        }

        visited[minIndex] = 1;  // Mark the selected request as visited
        totalSeek += minDistance;  // Add the seek distance to the total seek time
        head = queue[minIndex];  // Move the head to the selected request
        printf(" -> %d", head);  // Print the current request being serviced
    }

    printf("\nTotal seek distance: %d\n", totalSeek);  // Print the total seek distance
}

int main() {
    int head, size;
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the size of the request queue: ");
    scanf("%d", &size);

    int queue[size];
    printf("Enter the request queue: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &queue[i]);
    }

    // Call the SSTF function with the provided inputs
    sstf(queue, head, size);

    return 0;
}

//50
//7
//82 170 43 140 24 16 190