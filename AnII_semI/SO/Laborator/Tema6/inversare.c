#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void *inversare(void *t)
{
    char *text = t; //pun textul care trebuie inversat in variabila
    char *copie = (char*)malloc(strlen(text)+1); //aloc spatiul necesar pentru a inversa
    int i = 0;
    int l = strlen(text) - 1;
    while(i < strlen(text)) //pargul textul de la final la inceput
    {
        copie[i] = text[l];
        i++;
        l--;
    }
    copie[i] = '\0';

    return copie; //returnez textul inversat
}

int main(int argc, char *argv[])
{
    pthread_t thr; //declar un thread
    char *arg = argv[1];
    void *inv;
    if(pthread_create (&thr, NULL, inversare, arg )) //creez thread ul
    {
        perror(NULL);
        return errno;
    }

    if(pthread_join(thr, &inv)) //reunesc thread ul cu thread ul principal si pun ce a returnat functia in variabila inv
    {
        perror(NULL);
        return errno;
    }

    printf("Inainte de inversare: %s\nDupa inversare: %s\n", arg, inv); //afisez textul inainte si dupa inversare
    return 0;
}