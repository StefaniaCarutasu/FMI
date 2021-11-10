#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <math.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;

int decrease_count(int count)
{
    pthread_mutex_lock(&mtx);
    if(available_resources < count)
    {
        pthread_mutex_unlock(&mtx);
        return -1;
    }
    else
    {
        available_resources -= count;
        printf("got %d resources, %d remaining\n", count, available_resources);
    }

    pthread_mutex_unlock(&mtx);
    return 0;
}

int increase_count(int count)
{
    pthread_mutex_lock(&mtx);
    available_resources += count;
    printf("Released %d resources, %d remaining\n", count, available_resources);
    pthread_mutex_unlock(&mtx);

    return 0;
}

void *solve(void *v)
{
    int count = *(int *)v;
    decrease_count(count);
    increase_count(count);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thr[MAX_RESOURCES + 2];
    printf("Max resources = %d\n", available_resources);

    int i;
    int count;
    srand(time(0));
    for(i=0; i<MAX_RESOURCES; i++)
    {
        count = (rand() % MAX_RESOURCES) + 1;
        if(pthread_create(&thr[i], NULL, solve, &count))
        {
            perror(NULL);
            return errno;
        }
    }

    for(i=0; i<MAX_RESOURCES; i++)
    {
        pthread_join(thr[i], NULL);
    }

    pthread_mutex_destroy(&mtx);

    return 0;
}