/*#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define size 10000000

char v[size] = {'b'};
sem_t mtx;
char x;

void *scrie_a(void *arg)
{
    while (1)
    {
        sem_wait(&mtx);
        x = 'a';
        for (int i = 0; i < size; i++)
        {
            v[i] = 'a';
        }
        if(x != 'a')
            puts("Cineva a intra peste a");
        sem_post(&mtx);
    }
    return NULL;
}

void *scrie_b(void *arg)
{
    while (1)
    {
        sem_wait(&mtx);
        x = 'b';
        for (int i = 0; i < size; i++)
        {
            v[i] = 'b';
        }
        if(x != 'b')
            puts("Cineva a intra peste b");
        sem_post(&mtx);
    }
    return NULL;
}

void *citeste_v(void *arg)
{
    //pthread_mutex_lock(&mtx);
    while (1)
    {
        sem_wait(&mtx);
        x = 'c';
        char primul_byte = v[0];
        for (int i = 0; i < size; i++)
        {
            if (v[i] != primul_byte)
            {
                puts("!!!!!!!!!!!v este invalid!!!!!!!!!!");
                break;
            }
        }
        if(x != 'c')
            puts("Cineva a intra peste c");
        puts("v este valid");
        sem_post(&mtx);
    }
    //pthread_mutex_unlock(&mtx);
    return NULL;
}

int main()
{
    pthread_t thread_a, thread_b, thread_citeste;
    sem_init(&mtx, 0, 1);
    pthread_create(&thread_a, NULL, scrie_a, NULL);
    pthread_create(&thread_b, NULL, scrie_b, NULL);
    pthread_create(&thread_citeste, NULL, citeste_v, NULL);

    while (1)
        ;
    sem_destroy(&mtx);
}*/
#include <stdio.h>

int main()
{
    printf("Hello world!\n");
    return 0;
}