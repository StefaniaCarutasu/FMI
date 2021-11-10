#include<stdio.h>
#include<unistd.h>

int main()
{
    pid_t pid_copil=0;
    puts("Inainte de fork");

    pid_copil=fork();
    puts("Dupa fork");

    if(pid_copil==0)
    {
        //Executat doar de copil
        printf("Parent pid %d\n", getpid());
    }
    else
    {
        //Executat doar de parinte
        printf("Child pid %d\n", getpid());
    }
    return 0;
}