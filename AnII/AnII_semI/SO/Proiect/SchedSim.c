#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TimeSlice 10

struct TCB //TASK CONTROL BLOCK
{
    int prioritate;
    int timpExecutie;
    int momentStart;
    int momentFinish;
    int durataTotala;
    int timpRamas;
}proceseRR[10], proceseFCFS[10], rezultateRR[10], rezultateFCFS[10];


int main()
{

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0, nrProcese, moment, nr, j = 0, swap;
    float throughputFCFS, avgWaitFCFS = 0, avgCmpFCFS = 0, throughputRR, avgWaitRR = 0, avgCmpRR = 0;

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
            char* c = strtok(line, " ");
            proceseRR[i-1].prioritate = atoi(c);
            c = strtok(NULL, " ");
            proceseRR[i-1].timpExecutie = atoi(c);
            proceseRR[i-1].timpRamas = atoi(c);
            i++;
        } 
    }

    fclose(fp);
    if (line)
        free(line);

    swap = 1;
    while(swap == 1)
    {
        swap = 0;
        for(i = 1; i < nrProcese; i++)
            if(proceseRR[i - 1].prioritate < proceseRR[i].prioritate)
            {
                struct TCB new;
                new = proceseRR[i-1];
                proceseRR[i-1] = proceseRR[i];
                proceseRR[i] = new;
                swap = 1;
            }
    }

    for(i = 0; i < nrProcese; i++)
    {
        proceseFCFS[i] = proceseRR[i];
    }

    //Round Robin
    i = 0;
    moment = 0;
    nr = nrProcese;
    while (i < nr)
    {
        if(proceseRR[i].timpExecutie == proceseRR[i].timpRamas)
        {
            proceseRR[i].momentStart = moment;
        }
        if(proceseRR[i].timpRamas <= TimeSlice)
        {
            moment += proceseRR[i].timpRamas;
            proceseRR[i].momentFinish = moment;
            proceseRR[i].timpRamas = 0;
            proceseRR[i].durataTotala = proceseRR[i].momentFinish + proceseRR[i].momentStart;

            rezultateRR[j] = proceseRR[i];
            j++;

            for(int k = i; k < nr-1; k++)
                proceseRR[k] = proceseRR[k + 1];
            nr -= 1;
            i = 0;
        }
        else
        {
            proceseRR[i].timpRamas -= TimeSlice;
            moment += TimeSlice;
            if(i != nr)
            {
                if((i != 0 && proceseRR[i].prioritate == proceseRR[i + 1].prioritate) || i == 0)
                {
                    i++;
                }
                else
                {
                    i = 0;
                }
                
            }
        } 
    }

    //First come first served
    moment = 0;
    for(i = 0; i < nrProcese; i++)
    {
        proceseFCFS[i].momentStart = moment;
        moment += proceseFCFS[i].timpExecutie;
        proceseFCFS[i].momentFinish = moment;
        proceseFCFS[i].durataTotala = proceseFCFS[i].timpExecutie;
        proceseFCFS[i].timpRamas = 0;
        rezultateFCFS[i] = proceseFCFS[i];
    }

    //Afisare statistici
    printf("                           Statistici scheduler round-robin:\n");
    for(i = 0; i < nrProcese; i++)
    {
        printf("Prioritate: %d       Timp executie: %d       Moment start: %d       Moment finish: %d\n", rezultateRR[i].prioritate, rezultateRR[i].timpExecutie, rezultateRR[i].momentStart, rezultateRR[i].momentFinish);
    }
    printf("\n                 Statistici scheduler first come first served:\n");
    for(i = 0; i < nrProcese; i++)
    {
        printf("Prioritate: %d       Timp executie: %d       Moment start: %d       Moment finish: %d\n", rezultateFCFS[i].prioritate, rezultateFCFS[i].timpExecutie, rezultateFCFS[i].momentStart, rezultateFCFS[i].momentFinish);
    }

    throughputFCFS = ((float)nrProcese)/(float)(rezultateFCFS[nrProcese - 1].momentFinish);
    throughputRR = ((float)nrProcese)/(float)(rezultateRR[nrProcese - 1].momentFinish);

    for(i = 0; i < nrProcese; i++)
    {
        avgWaitRR += rezultateRR[i].momentStart;
        avgCmpRR += rezultateRR[i].momentFinish;
    }
    avgWaitRR = avgWaitRR / nrProcese;
    avgCmpRR = avgCmpRR / nrProcese;

    for(i = 0; i < nrProcese; i++)
    {
        avgWaitFCFS += rezultateFCFS[i].momentStart;
        avgCmpFCFS += rezultateFCFS[i].momentFinish;
    }
    avgWaitFCFS = avgWaitFCFS / nrProcese;
    avgCmpFCFS = avgCmpFCFS / nrProcese;

    printf("\n\n                                          Compararea celor doi algoritmi de scheduling\n");
    printf("\n                                          THROUGHPUT              AVG WAIT TIME               AVG COMPLETION TIME\n");
    printf("\nRount-Robin                                  %.2f                    %.2f                          %.2f", throughputRR, avgWaitRR, avgCmpRR);
    printf("\nFirst come first serve                       %.2f                    %.2f                          %.2f\n", throughputFCFS, avgWaitFCFS, avgCmpFCFS);

   return 0;
}