#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    char shm_name[] = "/collatzshm";
    int shm_fd;

    shm_fd = shm_open (shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_fd < 0)
    {
        perror(NULL);
        return errno;
    }

    size_t shm_size = 1024 * argc;

    if(ftruncate(shm_fd, shm_size) == -1)
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    int i = 0;

    while (argv[i] != '\0')
    {
        pid_t child = fork();
        if(child < 0)
            return errno;
        else 
        {
            int *addr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
            if(addr == MAP_FAILED)
            {
                perror(NULL);
                shm_unlink(shm_name);
                return errno;
            }

            int *buffer = addr + (i - 1)*1024/sizeof(int);
            int n = atoi(argv[i]);
            buffer[0] = n;
            int poz = 1;
            while (n > 1)
            {
                if(n % 2 == 0)
                    n = n / 2;
                else 
                    n = n * 3 + 1;
                buffer[poz] = n;
                poz = poz + 1;
            }
            printf("\nChild %d finished\nParent: %d", getpid(), getppid());
            return 0;
            
        }
        
    }

    while(wait(NULL) > 0);
    int *addr =  mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    int j;
    for(j = 1; j < argc; j++)
    {
        int *buff = addr + (j - 1)*1024/sizeof(int);
        int k = 0;
        while (buff[k] != 1)
        {
            printf("%d ", buff[k]);
            k = k + 1;
        }
        printf('\n');
    }

    munmap(addr, shm_size);
    shm_unlink("/collatzshm");
    return 0;
}