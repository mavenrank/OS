//! Also called as the Bounded Buffer Problem

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 10

int mutex = 1;
int full = 0;
int empty = N; // Initially, all slots are empty
int x = 0;

void producer()
{
    --mutex;       // Start of critical section
    full++;        // Increase the count of full slots
    empty--;       // Decrease the count of empty slots
    x++;           // Produce an item
    printf("Producer produces item %d\n", x);
    ++mutex;       // End of critical section
}

void consumer()
{
    --mutex;       // Start of critical section
    full--;        // Decrease the count of full slots
    empty++;       // Increase the count of empty slots
    printf("Consumer consumes item %d\n", x);
    x--;           // Consume the item
    ++mutex;       // End of critical section
}

int main()
{
    printf("\nType any Number\n1. Producer\n2. Consumer\n3. Exit\n");
    bool flag = true;
    int n;
    while (flag)
    {
        printf("Enter choice : ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            if ((mutex == 1) && (empty != 0))
                producer();
            else
                printf("Buffer is Full\n");
            break;

        case 2:
            if ((mutex == 1) && (full != 0))
                consumer();
            else
                printf("Buffer is Empty\n");
            break;

        case 3:
            flag = false;
            exit(0);
            break;

        default:
            printf("Invalid Choice\n");
        }
    }
    return 0;
}
