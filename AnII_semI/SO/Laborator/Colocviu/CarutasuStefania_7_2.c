#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>

#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

/* Mailul de la facultate */
char *email = "adriana.carutasu@s.unibuc.ro";
//Trebuie sa fac lab 7, Ex 2

/* Varibile pentru programul meu */
pthread_mutex_t mtx; //declar un mutex
sem_t sem; //declar un semafor
const int n = 5;
int contor; //cu variabila contor voi contoriza cate thread uri asteapta la barrier_point

pthread_t thr[10]; //vector de thread uri

void subiect()
{
    int i = 0;
    int suma = 9;
    while ('\0' != email[i])
    {
        suma = suma + (email[i] % 3);
        suma = suma % 3;
        i++;
    }
    switch (suma)
    {
    case 0:
        puts("Trebuie sa fac lab 5, Ex 2");
        break;
    case 1:
        puts("Trebuie sa fac lab 7, Ex 1");
        break;
    case 2:
        puts("Trebuie sa fac lab 7, Ex 2");
        break;
    default:
        puts("Oricare din cele de mai sus");
        break;
    }
}

/* Functii pentru programul meu */

int barrier_point()
{
    pthread_mutex_lock(&mtx); //blochez mutex-ul
    contor++; //incrementez numarul de thread-uri care au ajuns la bariera
    //cat timp nu sunt toate thread urile la bariera vor fi blocate in wait
    if(contor < n) //verific daca toate cele n thread uri au ajuns la bariera
    {  
        pthread_mutex_unlock(&mtx);   //deblochez mutex-ul
        if (sem_wait( &sem)) //nu permit trecerea mai departe daca nu sunt toate cele n thread-uri la bariera
        {
            perror(NULL);
            return errno;
        }
    }
    else //daca contorul este egal cu n inseamna ca toate thread-urile au ajuns la bariera
    {
        pthread_mutex_unlock(&mtx); 
        for(int i = 0; i < n - 1; i++)
        {
            if(sem_post( &sem ))
            {
                perror(NULL);
                return errno;
            }
        }  
        
    }
}

void *tfun(void *v)
{
    int tid = *(int *) v;

    printf("%d reached the barrier!\n", tid); //afisez faptul ca thread-ul cu id-ul tid a ajus la bariera
    barrier_point();
    printf("%d passed the barrier!\n", tid); //afisez faptul ca thread-ul cu id-ul tid a trecut de bariera

    return NULL;
}

int main(int argc, char *argv[])
{
    subiect();

    if(pthread_mutex_init(&mtx, NULL)) //initializez mutex-ul
    {
        perror(NULL);
        return errno;
    }

    if(sem_init(&sem, 0, 0)) //initializez semaforul
    {
        perror(NULL);
        return errno;
    }

    for (int i = 0; i < n; i++)
    {
        pthread_create(&thr[i], NULL, tfun, &i); //creez cele n thread uri
    }

    for(int i = 0; i < n; i++) //reunesc thread urile cu thread ul principal
    {
        if(pthread_join(thr[i], NULL))
        {
            perror(NULL);
            return errno;
        }
    }

    pthread_mutex_destroy(&mtx); //distrug mutex-ul
    sem_destroy(&sem); //distrug semaforul
    return 0;
}