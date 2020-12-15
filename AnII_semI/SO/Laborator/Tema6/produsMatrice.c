#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

int a[100][100]; //matrice 1
int b[100][100]; //matrice 2
int c[100][100]; //matricea rezultanta
int m1, m2, n1, n2; //dimensiunile matricelor

//calcularea elementului de pe pozitia ij in matricea c
void *element (void *arg) {
	int *rezultat = (int *)malloc(sizeof(int));
	int *argumente = (int *)arg;
	int i = argumente[0];
	int j = argumente[1];
	for(int k = 1; k <= m1; k++)
	{
		rezultat[0] += (a[i][k]*b[k][j]);
	}
	return rezultat;
}

int main()
{
    //citiri dimensiuni si matrice
    printf("Introduceti in ordine: n1, m1\n");
    scanf("%d %d", &n1, &m1);
    printf("Introduceti %d elemente\n", m1 * n1);
    for(int i = 0; i < n1; i++)
        for(int j = 0; j < m1; j++)
                scanf("%d", &a[i][j]);

    printf("Introduceti in ordine: n2, m2\n");
    scanf("%d %d", &n2, &m2);
    printf("Introduceti %d elemente\n", m2 * n2);
    for(int i = 0; i < n2; i++)
        for(int j = 0; j < m2; j++)
                scanf("%d", &b[i][j]);

    int contor = 0;
    pthread_t thr[100*100 + 1]; //facem un vector de thread-uri

    for(int i = 0; i < n1; i++)
    {
        for(int j = 0; j < m2; j++)
        {
            int *arg;
            arg = (int *)malloc(2 * sizeof(int));
            arg[0] = i;
            arg[1] = j;
            if(pthread_create(&thr[contor], NULL, element, arg))
            {
                perror(NULL);
                return errno;
            }

            contor++;
        }
    }

    contor = 0;

    for(int i = 0; i < n1; i++)
    {
        for(int j = 0; j < m2; j++)
        {
            int *res = (int *)malloc(sizeof(int));
            if(pthread_join(thr[contor], &res)) //aduce rezultatul din functiei in res
            {
                perror(NULL);
                return errno;
            }
            c[i][j] = *res;
            contor++;
        }
    }
    printf("Matricea rezultata este:\n");
    for(int i = 0; i < n1; i++)
    {
        for(int j = 0; j < m2; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }

    return 0;     

}