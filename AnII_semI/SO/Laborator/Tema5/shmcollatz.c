#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

void collatz (int *buffer, int n)
{
    buffer[0] = n;
    int i = 1;
    while(n != 1)
    {
        if(n % 2)
            n = 3 * n + 1;
        else
            n = n / 2;
       buffer[i] = n;
       i++;
    }
    return; 
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        puts("Nu ati dat suficiente argumente");
        return 0;
    }
    char shm_name[] = "/collatzshm"; 
    int shm_fd;

    shm_fd = shm_open (shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); //deschid shared memory
    if (shm_fd < 0) //daca nu s-a putut deschide 
    {
        perror(NULL);
        return errno;
    }
    
    size_t shm_size = 1024 * argc; //aloc memoria necesara

    if(ftruncate(shm_fd, shm_size) == -1)
    {
        perror(NULL);
        shm_unlink(shm_name); //sterg obiectele create cu shm_open
        return errno;
    }

    printf("Starting parent %d\n",getpid());
    int i = 1;

    while (i < argc)
    {
        int n = atoi(argv[i]);
        pid_t child = fork(); //creez copilul

        if(child < 0) //nu s-a putut crea copilul
            return errno;
        else
        {
            if(child == 0)
            {
                int *addr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0); //mapez memoria partajata pentru ca fiecare proces sa stie unde sa scrie
                if(addr == MAP_FAILED) //nu s-a reusit maparea
                {
                    perror(NULL);
                    shm_unlink(shm_name); //sterg obiectul creat
                    return errno;
                }

                int *buffer = addr + (i - 1) * 1024/ sizeof(int);
                collatz(buffer, n); //trimitem catre functia de collatz
                printf("Pid parinte: %d\nPid copil: %d\n", getppid(), getpid());
                return 0;
            }
        }
      i++;  
      munmap(shm_fd, shm_size); //a fost incarcata toata zona de memorie
    }

    while(wait(NULL) > 0); //asteapta toti copiii
    int *addr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0); //mapez iar pentru a putea afisa ce a scris fiecare copil in memorie
    for(int i = 1; i < argc; i ++) //afisez pentru fiecare argument in parte
    {
        int * buffer = addr+(i-1)*1024/sizeof(int); //ii spun de unde sa inceapa sa citeasca
        int j = 0;
        printf("%d: ", buffer[j]);
        while(buffer[j] != 1)
        {
            printf("%d ", buffer[j]);
            j++;
        }
        printf("1\n");
    }

    munmap(addr, shm_size); 
    shm_unlink("/collatz"); //sterge memoria creata la inceput
    return 0;
    
}