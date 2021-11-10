#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    pid_t child = fork();
    if(child < 0)
        return errno;
    else if(child == 0)
    {
         printf("%d: ", n);
         while(n > 1)
            if(n % 2 == 0)
            {
                n = n / 2;
                printf(" %d", n);
            }
            else
            {
                n = 3 * n + 1;
                printf(" %d", n);
            }
        printf("\nChild %d finished\n", getpid());            
    }
    else
    {
        wait(NULL);
    }

    return 0; 
}