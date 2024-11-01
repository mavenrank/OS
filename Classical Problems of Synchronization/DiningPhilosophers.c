#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
enum
{
    THINKING,
    HUNGRY,
    EATING
};
int state[N];
pthread_mutex_t mutex;
pthread_cond_t condition[N];
void test(int i);
void pick_up_forks(int i);
void put_down_forks(int i);
void *philosopher(void *num);
void test(int i)
{
    if (state[i] == HUNGRY && state[LEFT] != EATING &&
        state[RIGHT] != EATING)
    {
        state[i] = EATING;
        printf("Philosopher %d is eating\n", i + 1);
        sleep(1);
        pthread_cond_signal(&condition[i]);
    }
}
void pick_up_forks(int i)
{
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is hungry\n", i + 1);
    test(i);
    while (state[i] != EATING)
        pthread_cond_wait(&condition[i], &mutex);
    pthread_mutex_unlock(&mutex);
}
void put_down_forks(int i)
{
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d is thinking\n", i + 1);
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}
void *philosopher(void *num)
{
    int i = *(int *)num;
    while (1)
    {
        printf("Philosopher %d is thinking\n", i + 1);
        sleep(1);
        pick_up_forks(i);
        put_down_forks(i);
    }
}
int main()
{
    pthread_t thread_id[N];
    int philosopher_ids[N];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; i++)
    {
        pthread_cond_init(&condition[i], NULL);
        philosopher_ids[i] = i;
    }
    for (int i = 0; i < N; i++)
    {
        sleep(1);
        pthread_create(&thread_id[i], NULL, philosopher,
                       &philosopher_ids[i]);
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < N; i++)
    {
        pthread_cond_destroy(&condition[i]);
    }
    return 0;
}