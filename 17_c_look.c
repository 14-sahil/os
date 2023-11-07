#include <stdio.h>
#include <stdlib.h>

void cLook(int queue[], int head, int size, int direction, int diskSize) {
    int totalSeek = 0;  // Variable to keep track of the total seek distance
    int currentPosition = head;  // Variable to store the current head position

    // C-Look algorithm moving towards the right side of the disk
    if (direction == 1) {
        // Scan towards the right side
        for (int i = head; i < diskSize; i++) {
            for (int j = 0; j < size; j++) {
                if (queue[j] == i) {
                    totalSeek += abs(queue[j] - currentPosition);  // Calculate seek distance
                    currentPosition = queue[j];  // Move the head to the current request
                }
            }
        }
        // Continue scanning from the beginning of the disk to the initial head position
        for (int i = 0; i < head; i++) {
            for (int j = 0; j < size; j++) {
                if (queue[j] == i) {
                    totalSeek += abs(queue[j] - currentPosition);  // Calculate seek distance
                    currentPosition = queue[j];  // Move the head to the current request
                }
            }
        }
    }
    // C-Look algorithm moving towards the left side of the disk
    else {
        // Scan towards the left side
        for (int i = head; i >= 0; i--) {
            for (int j = 0; j < size; j++) {
                if (queue[j] == i) {
                    totalSeek += abs(queue[j] - currentPosition);  // Calculate seek distance
                    currentPosition = queue[j];  // Move the head to the current request
                }
            }
        }
        // Continue scanning from the end of the disk to the initial head position
        for (int i = diskSize - 1; i > head; i--) {
            for (int j = 0; j < size; j++) {
                if (queue[j] == i) {
                    totalSeek += abs(queue[j] - currentPosition);  // Calculate seek distance
                    currentPosition = queue[j];  // Move the head to the current request
                }
            }
        }
    }

    // Print the total seek distance
    printf("Total seek distance: %d\n", totalSeek);
}

int main() {
    int head, size, diskSize, direction;
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the size of the request queue: ");
    scanf("%d", &size);

    printf("Enter the disk size: ");
    scanf("%d", &diskSize);

    int queue[size];
    printf("Enter the request queue: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    // Call the C-Look function with the provided inputs
    cLook(queue, head, size, direction, diskSize);

    return 0;
}

//50
//7
//200
//82 170 43 140 24 16 190
//1