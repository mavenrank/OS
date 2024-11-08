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
