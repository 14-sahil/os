#include <stdio.h>

// the allocation , remaining need , maximum_needed
int max[10][10], allocation[10][10], need[10][10];

// how many reasources are available
int available[10];

// number of process and number of resources
int np, nr;
// this readMatrix is for taking the input from user
void readmatrix(int matrix[10][10])
{
    int i, j;
    for (i = 0; i < np; i++)
    {
        printf("\n Allocation for row %d ", i + 1);
        printf("\n");
        for (j = 0; j < nr; j++)
        {
            printf("\t column %d : ", j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// this display function will just display thinngs , nothing rocketScience
void display(int matrix[10][10])
{
    int i, j;
    for (i = 0; i < np; i++)
    {

        printf("\n P%d : ", i + 1);

        for (j = 0; j < nr; j++)
        {
            printf("%d \t", matrix[i][j]);
        }
    }
}

// calculate_need - we have to calculate need by subtracting the maximum_needed - allocated
void calculate_need()
{
    int i, j;
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {

            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Banker algo
void banker()
{
    int i, j, k = 0, flag;
    int finish[10], safe_seq[10];

    // this we took so we can indicate all process are incomplete by numbering them as 0
    for (i = 0; i < np; i++)
    {
        finish[i] = 0; // declares all process are incomplete
    }

    for (i = 0; i < np; i++)
    {
        flag = 0;

        // takes only those process which are incomplete
        if (finish[i] == 0)
        {

            // to check each resource of the need
            for (j = 0; j < nr; j++)
            {

                // need is greater then dont look the process as we cant satisfy the resources
                if (need[i][j] > available[j])
                {

                    flag = 1; // indicates not done , incomplete still
                    break;
                }
            }

            if (flag == 0)
            {
                finish[i] = 1; // this is to indicate that our needs are less or equal to the available one so process COMPLETED 

                // safe sequence is the sequence of process , means which process got completed first , so in array we will store the sequence of process completed

                safe_seq[k] = i + 1; // writing i+1 as here to display P1 instead of P0
                k++;

                // as process done now we have to give back the resources after execution so add that resources to available resources
                // lets give resources to garju people(process)

                for (j = 0; j < nr; j++)
                {
                    available[j] += allocation[i][j];
                }

                i = -1; // start  checking from up means first again for incomplete process
            }
        }
    }

    flag = 0;
    for (i = 0; i < np; i++)
    {
        if (finish[i] == 0)
        {
            printf("\n The system is in deadlock \n");
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        printf("\n The system is in safe state! \n Safe Sequence is --> ");
        for (i = 0; i < np; i++)
        {
            printf(" P%d", safe_seq[i]);
        }
    }
}

int main()
{
    int j;

    // read the input
    printf("\n Enter number of processess:");
    scanf("%d", &np);

    printf("\n Enter number of reasources: ");
    scanf("%d", &nr);

    printf("\n Enter initial allocation matrix: \n");
    readmatrix(allocation);

    printf("\n Enter max requirement matrix: \n");
    readmatrix(max);

    printf("\n Enter available reasources: \n");
    for (j = 0; j < nr; j++)
    {
        printf("\t Reasource %d : ", j + 1);
        scanf("%d", &available[j]);
    }

    // displaying the inputs one by one

    printf("\n ******************** Entered Data is ***************** \n \n");
    printf("\n Initial Allocation: \n");
    display(allocation);

    printf("\n Max Requirement: \n");
    display(max);

    printf("\n Available Resources: \n");
    for (j = 0; j < nr; j++)
    {
        printf("%d", available[j]);
    }

    calculate_need();
    printf("\n \n \n Need is : \n");
    display(need);

    banker();
    printf("\n \n \n");
    return 0;
}