#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>


#include <fcntl.h>
#include <pthread.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;

pthread_mutex_t mtx;

int decrease_count (int count)
{
    pthread_mutex_lock(&mtx); //inchid mutexul pentru a bloca firele de executie
    if(available_resources < count)
    {
        pthread_mutex_unlock(&mtx); //nu mai am resurse si deblochez mutexul
        return -1;
    }    
    else //am resursele necesare
    {
        available_resources -= count; //aloc resursele necesare
        printf("Got %d resources %d remaining\n", count, available_resources); //afisez cate resurse s-au consumat si cate mai sunt disponibile
    }

    pthread_mutex_unlock(&mtx);
    return 0;  
}

int increase_count (int count)
{
    pthread_mutex_lock(&mtx);
    available_resources += count;
    printf("Released %d resources remaining %d\n", count, available_resources);
    pthread_mutex_unlock(&mtx);

    return 0;
}

void *count (void *arg)
{
    int count = * (int *) arg;

    while (decrease_count(count) == -1); //cat timp nu exista numarul de resurse necesar va astepta
    increase_count(count); //elibereaza resursele

    return NULL;
}

int main()
{
    int nr_resurse;
    //initializez mutexul
    if(pthread_mutex_init(&mtx, NULL))
    {
        perror(NULL);
        return errno;
    }

    pthread_t thr[MAX_RESOURCES + 2]; //facem un vector pentru a retine id-urile thread-urilor
    printf("MAX_RESOURCES = %d\n", MAX_RESOURCES);
    for(int i = 0; i < MAX_RESOURCES; i++) //urmeaza sa creez MAX_RESOURCES thread-uri
    {
        nr_resurse = rand() % (MAX_RESOURCES + 1); //numar random de resurse
        if(pthread_create(&thr[i], NULL, count, &nr_resurse)) //creez thread-ul
            {
                perror(NULL);
                return errno;
            }
    }

    for (int i = 0; i < MAX_RESOURCES; i++)
        if(pthread_join(thr[i], NULL))
        {
            perror(NULL);
            return errno;
        }
    
    pthread_mutex_destroy(&mtx);

    return 0;
}