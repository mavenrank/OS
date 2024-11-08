#include <stdio.h>

#define MAX 10

void firstFit(int blockSize[], int m, int processSize[], int n);
void bestFit(int blockSize[], int m, int processSize[], int n);
void worstFit(int blockSize[], int m, int processSize[], int n);

int main()
{
    int blockSize[MAX], processSize[MAX];
    int m, n, i;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter sizes of %d memory blocks: ", m);
    for (i = 0; i < m; i++)
    {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter sizes of %d processes: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &processSize[i]);
    }

    int blockCopy[MAX];

    for (i = 0; i < m; i++)
    {
        blockCopy[i] = blockSize[i];
    }
    firstFit(blockCopy, m, processSize, n);

    for (i = 0; i < m; i++)
    {
        blockCopy[i] = blockSize[i];
    }
    bestFit(blockCopy, m, processSize, n);

    for (i = 0; i < m; i++)
    {
        blockCopy[i] = blockSize[i];
    }
    worstFit(blockCopy, m, processSize, n);

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
