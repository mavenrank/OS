#include <stdio.h>

#define MAX 10 // Maximum number of blocks and processes

// Function declarations
void firstFit(int blockSize[], int m, int processSize[], int n);
void bestFit(int blockSize[], int m, int processSize[], int n);
void worstFit(int blockSize[], int m, int processSize[], int n);

int main()
{
    int blockSize[MAX], processSize[MAX];
    int m, n, i, choice;

    // Input number of blocks and their sizes
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter sizes of %d memory blocks: ", m);
    for (i = 0; i < m; i++)
    {
        scanf("%d", &blockSize[i]);
    }

    // Input number of processes and their sizes
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter sizes of %d processes: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &processSize[i]);
    }

    // Choose allocation algorithm
    printf("Choose memory allocation algorithm:\n");
    printf("1. First Fit\n");
    printf("2. Best Fit\n");
    printf("3. Worst Fit\n");
    printf("Enter choice (1/2/3): ");
    scanf("%d", &choice);

    // Copy original block sizes for each allocation method
    int blockCopy[MAX];
    for (i = 0; i < m; i++)
    {
        blockCopy[i] = blockSize[i];
    }

    // Call the selected allocation algorithm
    switch (choice)
    {
    case 1:
        firstFit(blockCopy, m, processSize, n);
        break;
    case 2:
        bestFit(blockCopy, m, processSize, n);
        break;
    case 3:
        worstFit(blockCopy, m, processSize, n);
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }

    return 0;
}

// First Fit Algorithm
void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d allocated to block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

// Best Fit Algorithm
void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];
    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        allocation[i] = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d allocated to block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

// Worst Fit Algorithm
void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];
    for (int i = 0; i < n; i++)
    {
        int worstIdx = -1;
        allocation[i] = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d allocated to block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}
