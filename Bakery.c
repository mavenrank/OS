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