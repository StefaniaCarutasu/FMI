#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main()
{
    pid_t child;
    child = fork();
    if(child == -1)
        return -1;
    if(child != 0)
    {
        
        wait(NULL);
        printf("My pid:\t%d\n Child pid:\t%d\n", getpid(), child);
    }
    else
    {
        printf("My pid:\t%d\n Child pid:\t%d\n", getppid(), getpid());
        char *argv[] = {"/bin/ls", NULL};
        char *envp[] = {NULL};
        execve("/bin/ls", argv, envp);
    }
}