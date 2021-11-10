#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t child = fork();
    if (child == -1)
        return -1;
    if(child != 0)
    {
        wait(NULL);
        printf("My pid:\t%d\n Child pid\t%d\n", getpid(), childpid());
    }
    else
    {
        printf("My pid:\t%d\n Child pid\t%d\n", getppid(), getpid());

        char *argv[] = {"/bin/ls", NULL};
        char *envp[] = {NULL};
        exceve("/bin/ls", argv, envp);
    }
    
    return 0;
}