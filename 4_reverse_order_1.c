#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    /* argv[0] is the program name */
    if (argc <= 2) {
        printf("Usage: %s [number1] [number2] ... [numberN]\n", argv[0]);
        return 1;
    }

    // Printing Element in Reverse
    printf("\n Printing Element in Reverse:");
    for(int i = argc-1; i>0; i--)
        printf("%c ", argv[i][0]); // Access the first character of each argument
    
    printf("\n\n EXECV task Completed \n");
    return 0;
}


//  PART-2 

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void bubbleSort(char arr[], int n)
{
    char temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            
        }
        
    }

    printf("\nAscending Order:\n");
    for (int i = 0; i < n; i++)
        printf("%c ", arr[i]);
    printf("\nSorting Completed\n");
    
}

int main()
{
    int n=0;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    char arr[n];

    printf("Enter the elements in the array: ");
    for (int i = 0; i < n; i++)
        scanf(" %c", &arr[i]);

    bubbleSort(arr, n);

    pid_t cid = fork();

    if (cid > 0)
    {
        printf("\n\nPARENT PROCESS\n");
        printf("It's id: %d", getpid());
        printf("\nParent is waiting for child to complete.");

        wait(NULL);

        printf("\n\nParent Process Finished\n");
    }
    else if (cid == 0)
    {
        sleep(3);
        printf("\n\nCHILD PROCESS\n");
        printf("It's id: %d", getpid());
        printf("Parent's id: %d", getppid());

        printf("Child is calling EXEC()");

        // char array named program to store the compiled file of the child
        char program[] = "./child"; 

        // +2 for program name and NULL
        char *arguments[n + 2];

        // Setting 0th argument as the char array of program
        arguments[0] = program;
        for (int i = 0; i < n; i++)
        {
            arguments[i + 1] = (char *)malloc(2);
            sprintf(arguments[i + 1], "%c", arr[i]);
        }
        arguments[n + 1] = NULL;

        execv(program, arguments);
        perror("execv");

        printf("\n\n Child EXECV Call Complete\n"); //Ideally this should not be printed
        printf("\n\n Child Execution Complete \n");
    }
    return 0;
}

// execv() - 
// The execv() function executes a process from another process or program.
// It takes two parameters - i)path  
//                           ii)arguments array

// i)Path
// This function executes the file or executable which is specified in the *path argument.
// This entry should contain the absolute or relative path of the executable file in string format.

// ii)Arguments array
// The *argv[] argument is an array of pointers to strings where each string is an input argument
// that is passed to the process to be executed.
// The first pointer of the array should always point to a string that contains the name of the 
// executable file and the last pointer should always be NULL.
