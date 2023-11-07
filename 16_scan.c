#include <stdio.h>
#include <stdlib.h>

void scan(int queue[], int head, int size, int direction, int diskSize) {
    int seekSequence[size + 1];  // Array to store the sequence in which requests are serviced
    int totalSeek = 0;  // Variable to keep track of the total seek distance
    int currentPosition = head;  // Variable to store the current head position

    int left = 0;  // Index for the left side of the disk
    int right = diskSize - 1;  // Index for the right side of the disk

    int index = 0;  // Index for the seekSequence array

    // Initialize the seekSequence array
    for (int i = 0; i < size; i++) {
        seekSequence[i] = -1;
    }

    // Add the initial head position to the seekSequence array
    seekSequence[index++] = head;

    // SCAN algorithm moving towards the right side of the disk
    if (direction == 1) {
        // Scan towards the right side
        for (int i = head; i < diskSize; i++) {
            for (int j = 0; j < size; j++) {
                if (queue[j] == i) {
                    seekSequence[index++] = i;
                    queue[j] = -1;  // Mark the serviced request as -1
                }
            }
        }
        // Scan towards the left side after reaching the right end
        for (int i = right; i >= 0; i--) {
            for (int j = 0; j < size; j++) {
                if (queue[j] == i) {
                    seekSequence[index++] = i;
                    queue[j] = -1;  // Mark the serviced request as -1
                }
            }
        }
    }
    // SCAN algorithm moving towards the left side of the disk
    else {
        // Scan towards the left side
        for (int i = head; i >= 0; i--) {
            for (int j = 0; j < size; j++) {
                if (queue[j] == i) {
                    seekSequence[index++] = i;
                    queue[j] = -1;  // Mark the serviced request as -1
                }
            }
        }
        // Scan towards the right side after reaching the left end
        for (int i = left; i < diskSize; i++) {
            for (int j = 0; j < size; j++) {
                if (queue[j] == i) {
                    seekSequence[index++] = i;
                    queue[j] = -1;  // Mark the serviced request as -1
                }
            }
        }
    }

    // Calculate total seek distance
    for (int i = 0; i < size; i++) {
        if (seekSequence[i + 1] != -1) {
            totalSeek += abs(seekSequence[i + 1] - seekSequence[i]);
        }
    }

    // Print the seek sequence
    printf("Seek Sequence: ");
    for (int i = 0; i < index; i++) {
        printf("%d ", seekSequence[i]);
    }
    printf("\nTotal seek distance: %d\n", totalSeek);
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

    // Call the SCAN function with the provided inputs
    scan(queue, head, size, direction, diskSize);

    return 0;
}

//50
//7
//200
//82 170 43 140 24 16 190
//1