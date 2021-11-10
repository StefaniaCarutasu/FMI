#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int i = 1;
    while (i < argc)
    {
        pid_t child = fork();
        if(child < 0)
            return(errno);
        else if(child == 0)
        {
            int n = atoi(argv[i]);
            printf("\n%d: ", n);
            while (n > 1)
                if (n % 2 == 0)
                {
                    n = n / 2;
                    printf(" %d", n);
                }
                else
                {
                     n = 3 * n + 1;
                    printf(" %d", n);
                }

            printf("\nChild %d finished\nParent: %d\n", getpid(), getppid());   
            return 1;
        }
        
        i++;
    }

     for(i = 1; i <= argc; i++)
        wait(NULL);

    printf("Done Parent %d Me %d\n", getppid(), getpid());
    return 0;
}