#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Function to perform sorting (bubble sort in this case)
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int size;
    printf("Enter the number of integers: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter %d integers: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork(); // Create a child process using fork system call

    if (pid < 0) {
        // Forking failed
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process ID: %d\n", getpid());
        bubbleSort(arr, size); // Sort the integers in the child process
        printf("Child process sorted the integers.\n");
    } else {
        // Parent process
        printf("Parent process ID: %d\n", getpid());

        // Demonstrate orphan state by allowing the parent to finish execution first
        sleep(2);
        printf("Parent process finished.\n");
    }

    return 0;
}
