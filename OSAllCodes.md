# All OS Lab Codes

## Basic Shell Programming

### Printing

```bash
#!/bin/bash
echo "Hello, World!"

name="Mav"
echo "Hello, $name!"
```

### Reading

```bash
#!/bin/bash
echo "Enter your name: "
read name
echo "Hello, $name!"
```

### If else statements

```bash
#!/bin/bash
echo "Enter a number: "
read num

if [ $num -gt 10 ]; then
    echo "The number is greater than 10."
else
    echo "The number is 10 or less."
fi
```

### Expressions

```bash
#!/bin/bash

a=5
b=3

sum=$((a + b))
echo "Sum: $sum"

product=$(expr $a \* $b)
echo "Product: $product"

difference=$(expr $a \- $b)
echo "Difference: $difference"
```

### Functions

```bash
#!/bin/bash
add (){
    num1=$1
    num2=$2
    echo "Sum of the two numbers : $((num1+num2))"
}
echo "enter a number : "
read num1
echo "enter another number : "
read num2
add $num1 $num2
```

### Greatest of Two Numbers

```bash
#!/bin/bash
echo "Enter a number"
read num1
echo "Enter another number"
read num2

if [ $num1 -gt $num2 ];
    then echo "$num1 is greater than $num2"
else
    echo "$num2 is greater than $num1"
fi
```

### Loops and Case Statements

```bash
#!/bin/bash

for i in 1 2 3 4 5
do
  echo "Number: $i"
done

counter=1
while [ $counter -le 5 ]
do
  echo "Counter: $counter"
  ((counter++))
done

counter=1
until [ $counter -gt 5 ]; do
    echo "Counter: $counter"
    ((counter++))
done

echo "Enter a character: "
read char
case $char in
  [a-z] )
    echo "You entered a lowercase letter."
    ;;
  [A-Z] )
    echo "You entered an uppercase letter."
    ;;
  [0-9] )
    echo "You entered a digit."
    ;;
  * )
    echo "You entered a special character."
    ;;
esac
```

### Test program - Fibonacci Series

```bash
#!/bin/bash

first=0
second=1

read -p "Enter the number of terms:" n
echo "Fibonacci series up to $n terms:"
echo $first
echo $second
count=2
while [ $count -lt $n ]; do
    temp=`expr $first + $second`
    echo $temp
    first=$second
    second=$temp
    count=$((count + 1))
done
```

## Classical Problems of Synchronization

### Producer and Consumer

```c
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
```

## DeadLock Prevention

### Bakery Algorithm

```c
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#define THREAD_COUNT 8
volatile int thread_tickets[THREAD_COUNT];
volatile int thread_choosing[THREAD_COUNT];
volatile int shared_resource;
void acquire_lock(int thread_id)
{
    thread_choosing[thread_id] = 1;
    int max_ticket_number = 0;
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        int current_ticket = thread_tickets[i];
        if (current_ticket > max_ticket_number)
        {
            max_ticket_number = current_ticket;
        }
    }
    thread_tickets[thread_id] = max_ticket_number + 1;
    thread_choosing[thread_id] = 0;
    for (int other_thread_id = 0; other_thread_id < THREAD_COUNT;
         ++other_thread_id)
    {
        while (thread_choosing[other_thread_id])
        {
            // Wait until the other thread finishes choosing its ticket
        }
        while (thread_tickets[other_thread_id] != 0 &&
               (thread_tickets[other_thread_id] <
                    thread_tickets[thread_id] ||
                (thread_tickets[other_thread_id] ==
                     thread_tickets[thread_id] &&
                 other_thread_id < thread_id)))
        {
            // Wait if another thread has priority
        }
    }
}
void release_lock(int thread_id)
{
    thread_tickets[thread_id] = 0;
}
void access_shared_resource(int thread_id)
{
    if (shared_resource != 0)
    {
printf("Thread %d acquired the resource, but it's still in-use by thread %d!\n", thread_id, shared_resource);
    }
    shared_resource = thread_id;
    printf("Thread %d is using the shared resource.\n", thread_id);
    sleep(2);
    shared_resource = 0;
}
void *thread_routine(void *arg)
{
    intptr_t thread_id = (intptr_t)arg;
    acquire_lock(thread_id);
    access_shared_resource(thread_id);
    release_lock(thread_id);
    return NULL;
}
int main(int argc, char **argv)
{
    memset((void *)thread_tickets, 0, sizeof(thread_tickets));
    memset((void *)thread_choosing, 0, sizeof(thread_choosing));
    shared_resource = 0;
    pthread_t threads[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        pthread_create(&threads[i], NULL, thread_routine, (void *)((intptr_t)i));
    }
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
```

## DeadLock Avoidance

### Banker's Algortihm

```c
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#define THREAD_COUNT 8
volatile int thread_tickets[THREAD_COUNT];
volatile int thread_choosing[THREAD_COUNT];
volatile int shared_resource;
void acquire_lock(int thread_id)
{
    thread_choosing[thread_id] = 1;
    int max_ticket_number = 0;
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        int current_ticket = thread_tickets[i];
        if (current_ticket > max_ticket_number)
        {
            max_ticket_number = current_ticket;
        }
    }
    thread_tickets[thread_id] = max_ticket_number + 1;
    thread_choosing[thread_id] = 0;
    for (int other_thread_id = 0; other_thread_id < THREAD_COUNT;
         ++other_thread_id)
    {
        while (thread_choosing[other_thread_id])
        {
            // Wait until the other thread finishes choosing its ticket
        }
        while (thread_tickets[other_thread_id] != 0 &&
               (thread_tickets[other_thread_id] <
                    thread_tickets[thread_id] ||
                (thread_tickets[other_thread_id] ==
                     thread_tickets[thread_id] &&
                 other_thread_id < thread_id)))
        {
            // Wait if another thread has priority
        }
    }
}
void release_lock(int thread_id)
{
    thread_tickets[thread_id] = 0;
}
void access_shared_resource(int thread_id)
{
    if (shared_resource != 0)
    {
        printf("Thread %d acquired the resource, but it's still in-use by thread %d!\n", thread_id, shared_resource);
    }
    shared_resource = thread_id;
    printf("Thread %d is using the shared resource.\n", thread_id);
    sleep(2);
    shared_resource = 0;
}
void *thread_routine(void *arg)
{
    intptr_t thread_id = (intptr_t)arg;
    acquire_lock(thread_id);
    access_shared_resource(thread_id);
    release_lock(thread_id);
    return NULL;
}
int main(int argc, char **argv)
{
    memset((void *)thread_tickets, 0, sizeof(thread_tickets));
    memset((void *)thread_choosing, 0, sizeof(thread_choosing));
    shared_resource = 0;
    pthread_t threads[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        pthread_create(&threads[i], NULL, thread_routine, (void *)((intptr_t)i));
    }
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
```

## Forks Related

### Simple Fork

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if (pid < 0){
        perror("Fork Failed");
        return 1;
    }
    else if(pid == 0){
        printf("Child Process PID : %d", getpid());
        printf("Parent Process PID : %d", getppid());
    }
    else{
        printf("Parent Process : %d", getpid());
        printf("Child PID : %d", pid);
        wait(NULL);
    }
    return 0;
}
```

### Orphan Process

```c
//? Write a C program to create a Orphan Process

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
    pid_t pid = fork();
    if (pid < 0){
        perror("Fork Failed");
        return 1;
    }
    else if (pid == 0){
        sleep(5);
        printf("Child Process (orphan)");
        printf("Child Process PID : %d", getpid());
        printf("New Parent PID : %d", getppid());
    }
    else {
        printf("Parent Process");
        printf("Parent Process PID : %d", getpid());
        printf("Child Process PID : %d", pid);
        printf("Parent Terminating...");
        exit(0);
    }
}
```

### Zombie Process

```c
//? Write a C program to create a Zombie Process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid = fork();
    if (pid == 0){
        printf("Child Process PID : %d", getpid());
        sleep(2);
        printf("Child Process %d terminating", getpid());
        exit(0);
    }
    else if (pid > 0){
        printf("Parent PID : %d", getpid());
        sleep(10);
        printf("Parent PID %d is exiting", getpid());
    }
    return 0;
}

//! In the above code, the child becomes a zombie process because the parent has not called wait()
```

### Fork and Terminate The child and print the state of termination

```c
//? Write a proram which creates a child process, waits for termination of its child and then lists its PID
//? together with the state in which the process was terminated

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int states;
    pid_t pid = fork();
    if (pid < 0){
        perror("Fork Failed");
        return 1;
    }
    else if (pid == 0){
        printf("Child process PID : %d", getpid());
        sleep(2);
        exit(0);
    }
    else{
        printf("Parent Process Waiting for child not Terminate");
        waitpid(pid, &states, 0);
        if (WIFEXITED(states)){
            printf("Child Process PID : %d", pid, WIFEXITED(states));
        }
        else if (WIFSIGNALED(states)){
            printf("Child Process PID : %d terminated by synd = %d", pid, WTERMSIG(states));
        }
        else{
            printf("Child Process PID : %d terminated abnormally", pid);
        }
    }
}
```

## Inter Process Communication

### Using IPC Message Queue

```c
//? Implement a C program to create a message queue by sending a message and then receive the
//? message in reverse via the message queue.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 100

// Define the message structure
struct message {
    long msg_type;
    char text[MAX_TEXT];
};

// Function to reverse a string
void reverse_string(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate a unique key
    key = ftok("msgqueuefile", 65);

    // Create a message queue and check for errors
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Input a message from the user
    printf("Enter a message: ");
    fgets(msg.text, sizeof(msg.text), stdin);
    msg.text[strcspn(msg.text, "\n")] = 0; // Remove the newline character

    // Set message type for the original message
    msg.msg_type = 1;

    // Send the original message to the queue
    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
        perror("msgsnd failed for original message");
        exit(1);
    }

    printf("Original message sent: %s\n", msg.text);

    // Reverse the message
    reverse_string(msg.text);

    // Set message type for the reversed message
    msg.msg_type = 2;

    // Send the reversed message to the queue
    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
        perror("msgsnd failed for reversed message");
        exit(1);
    }

    printf("Reversed message sent: %s\n", msg.text);

    // Receive the reversed message using msg_type = 2
    struct message received_msg;
    if (msgrcv(msgid, &received_msg, sizeof(received_msg.text), 2, 0) == -1) {
        perror("msgrcv failed for reversed message");
        exit(1);
    }

    printf("Reversed message received: %s\n", received_msg.text);

    // Destroy the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    return 0;
}
```

### Using Shared Memory to Read and Write

#### Reader Code

```c
//? Implement IPC using IPC.h header file.

//! This is the reader file
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of the shared memory

int main() {
    key_t key = ftok("shmfile", 65);  // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666);  // Get the shared memory

    char *str = (char *)shmat(shmid, NULL, 0);  // Attach to the shared memory

    printf("Data read from memory: %s\n", str);  // Read the data

    shmdt(str);  // Detach from shared memory
    shmctl(shmid, IPC_RMID, NULL);  // Destroy the shared memory
    return 0;
}
```

#### Writer Code

```c
//! This is the writer file

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of the shared memory

int main() {
    key_t key = ftok("shmfile", 65);  // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);  // Create shared memory

    char *str = (char *)shmat(shmid, NULL, 0);  // Attach to the shared memory

    printf("Write Data: ");
    fgets(str, SHM_SIZE, stdin);  // Get input from the user

    printf("Data written in memory: %s\n", str);

    shmdt(str);  // Detach from shared memory
    return 0;
}
```
## CPU Scheduling 

### SJF, FCFS, Priority and Round Robin

```c
#include <stdio.h>
#define MAX_PROCESSES 5
typedef struct
{
    int process_id;
    int burst_time;
    int arrival_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int response_time;
} Process;

void calculate_waiting_and_turnaround_time(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;

        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void calculate_average_times(Process processes[], int n)
{
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("Average waiting time:%.2f ms\n", (float)total_waiting_time / n);
    printf("Average turnaround time:%.2f ms\n", (float)total_turnaround_time / n);
}
void fcfs(Process processes[], int n)
{
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < processes[i].arrival_time)
        {
            current_time = processes[i].arrival_time;
        }
        processes[i].response_time = current_time - processes[i].arrival_time;
        processes[i].completion_time = current_time + processes[i].burst_time;
        current_time = processes[i].completion_time;
    }
    calculate_waiting_and_turnaround_time(processes, n);
}
void sjf(Process processes[], int n)
{
    int completed = 0, current_time = 0;
    int is_completed[MAX_PROCESSES] = {0};
    while (completed != n)
    {
        int idx = -1;
        int min_burst_time = 9999;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && !is_completed[i])
            {
                if (processes[i].burst_time < min_burst_time)
                {
                    min_burst_time = processes[i].burst_time;
                    idx = i;
                }
            }
        }
        if (idx != -1)
        {
            processes[idx].response_time = current_time - processes[idx].arrival_time;
            processes[idx].completion_time = current_time + processes[idx].burst_time;
            current_time = processes[idx].completion_time;
            is_completed[idx] = 1;
            completed++;
        }

        else
        {
            current_time++;
        }
    }
    calculate_waiting_and_turnaround_time(processes, n);
}

void priority_scheduling(Process processes[], int n)
{
    int completed = 0, current_time = 0;
    int is_completed[MAX_PROCESSES] = {0};
    while (completed != n)
    {
        int idx = -1;
        int highest_priority = 9999;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && !is_completed[i])
            {
                if (processes[i].priority < highest_priority)
                {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }
        if (idx != -1)
        {
            processes[idx].response_time = current_time - processes[idx].arrival_time;
            processes[idx].completion_time = current_time + processes[idx].burst_time;
            current_time = processes[idx].completion_time;
            is_completed[idx] = 1;
            completed++;
        }
        else
        {
            current_time++;
        }
    }
    calculate_waiting_and_turnaround_time(processes, n);
}

void round_robin(Process processes[], int n, int quantum)
{
    int remaining_burst_time[MAX_PROCESSES];
    int completed = 0, current_time = 0;
    for (int i = 0; i < n; i++)
    {
        remaining_burst_time[i] = processes[i].burst_time;
    }

    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && remaining_burst_time[i] > 0)
            {
                if (remaining_burst_time[i] < processes[i].burst_time)
                {
                    processes[i].response_time = current_time - processes[i].arrival_time;
                }
                if (remaining_burst_time[i] > quantum)
                {
                    current_time += quantum;
                    remaining_burst_time[i] -= quantum;
                }
                else
                {
                    current_time += remaining_burst_time[i];
                    remaining_burst_time[i] = 0;
                    processes[i].completion_time = current_time;
                    completed++;
                }
            }
        }
    }
    calculate_waiting_and_turnaround_time(processes, n);
}

void print_table(Process processes[], int n)
{
    printf("\nP#\tAT\tBT\tPRI\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time, processes[i].response_time);
    }
}

int main()
{
    Process processes[MAX_PROCESSES];
    printf("Enter the details in the order of Process ID, Burst Time, Arrival Time, Priority:\n");

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        printf("Enter the details for Process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &processes[i].process_id);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        printf("\n");
    }

    int n = MAX_PROCESSES;
    printf("First-come-first-serve scheduling:\n");
    fcfs(processes, n);
    print_table(processes, n);
    calculate_average_times(processes, n);

    printf("\nShortest-job-first scheduling:\n");
    sjf(processes, n);
    print_table(processes, n);
    calculate_average_times(processes, n);

    printf("\nPriority scheduling:\n");
    priority_scheduling(processes, n);
    print_table(processes, n);
    calculate_average_times(processes, n);

    printf("\nRound Robin scheduling (Quantum=2ms):\n");
    round_robin(processes, n, 2);
    print_table(processes, n);
    calculate_average_times(processes, n);
    printf("P = Process ID\n");
    printf("AT = Arrival Time\n");
    printf("BT = Burst Time\n");
    printf("PRI = Priority\n");
    printf("CT = Completion Time\n");
    printf("TAT = Turnaround Time\n");
    printf("WT = Waiting Time\n");
    printf("RT = Response Time\n");
    return 0;
}

```

## Memory Scheduling

### Best, First and Worst Fit

```c
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
```

## Page Replacement Algorithms

```c
#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// Function to check if a page is already in a frame
bool isPageInFrames(int page, int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) return true;
    }
    return false;
}

// FIFO Page Replacement
int fifoPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES], pageFaults = 0;
    int index = 0;  // Next frame to replace

    for (int i = 0; i < numFrames; i++) frames[i] = -1;  // Initialize frames

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrames(pages[i], frames, numFrames)) {
            frames[index] = pages[i];
            index = (index + 1) % numFrames;
            pageFaults++;
        }
    }

    return pageFaults;
}

// LRU Page Replacement
int lruPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES], pageFaults = 0;
    int counter[MAX_FRAMES] = {0};  // Keeps track of when each page was last used

    for (int i = 0; i < numFrames; i++) frames[i] = -1;  // Initialize frames

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrames(pages[i], frames, numFrames)) {
            int lruIndex = 0;
            for (int j = 1; j < numFrames; j++) {
                if (frames[j] == -1 || counter[j] < counter[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = pages[i];
            pageFaults++;
        }
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] != -1) counter[j]++;
            if (frames[j] == pages[i]) counter[j] = 0;  // Reset counter for used page
        }
    }

    return pageFaults;
}

// Optimal Page Replacement
int optimalPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES], pageFaults = 0;

    for (int i = 0; i < numFrames; i++) frames[i] = -1;  // Initialize frames

    for (int i = 0; i < numPages; i++) {
        if (!isPageInFrames(pages[i], frames, numFrames)) {
            int replaceIndex = -1, farthestDistance = -1;
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
                int k;
                for (k = i + 1; k < numPages; k++) {
                    if (frames[j] == pages[k]) break;
                }
                if (k > farthestDistance) {
                    farthestDistance = k;
                    replaceIndex = j;
                }
            }
            frames[replaceIndex] = pages[i];
            pageFaults++;
        }
    }

    return pageFaults;
}

// Main function
int main() {
    int numPages, numFrames;
    int pages[MAX_PAGES];

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    printf("Enter the page reference sequence: ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    // Calculate page faults for each algorithm
    int fifoFaults = fifoPageReplacement(pages, numPages, numFrames);
    int lruFaults = lruPageReplacement(pages, numPages, numFrames);
    int optimalFaults = optimalPageReplacement(pages, numPages, numFrames);

    // Display results
    printf("\nPage Replacement Algorithms Results:\n");
    printf("FIFO Page Faults: %d\n", fifoFaults);
    printf("LRU Page Faults: %d\n", lruFaults);
    printf("Optimal Page Faults: %d\n", optimalFaults);

    return 0;
}
```
