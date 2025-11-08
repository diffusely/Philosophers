#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];

void* philosopher(void* arg)
{
    int id = (long)arg;
    int left  = id;
    int right = (id + 1) % N;

    // ordering rule:
    int first  = left  < right ? left  : right;
    int second = left  < right ? right : left;

    while (1)
    {
        // thinking
        printf("Philosopher %d thinking\n", id);
        usleep(200000);

        // take forks
        pthread_mutex_lock(&forks[first]);
        pthread_mutex_lock(&forks[second]);

        printf("Philosopher %d eating\n", id);
        usleep(200000);

        // release forks
        pthread_mutex_unlock(&forks[second]);
        pthread_mutex_unlock(&forks[first]);
    }
    return NULL;
}

int main()
{
    pthread_t ph[N];

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&forks[i], NULL);

    for (int i = 0; i < N; i++)
        pthread_create(&ph[i], NULL, philosopher, (void*)(long)i);

    for (int i = 0; i < N; i++)
        pthread_join(ph[i], NULL);

    return 0;
}
