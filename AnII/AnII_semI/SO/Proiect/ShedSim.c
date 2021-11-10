
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct proces
{
    int timpExecutie;
    int momentStart;
    int momentFinish;
    int durataTotala;
    int timpRamas;
};

struct nod
{
    struct proces p;
    int prioritate;
    struct nod* next;
}head, start;

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0, nrProcese;

    fp = fopen("procese.in.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) 
    {
        if(i == 0)
        {
            i++;
            nrProcese = atoi(line);
        }
        else
        {
            if(i == 1)
            {
                i++;
                char * token = strtok(line, " ");
                head.prioritate = atoi(token);
                token = strtok(NULL, " ");
                head->p->timpExecutie = atoi(token);
                start = *head;
                head = head->next;
            }
            else
            {
                nod *proces = NULL;
                proces = new nod();

                char * token = strtok(line, " ");
                head.prioritate = atoi(token);
                token = strtok(NULL, " ");
                head->p->timpExecutie = atoi(token);
                head = head->next;
            }   
        }  

    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
    
}