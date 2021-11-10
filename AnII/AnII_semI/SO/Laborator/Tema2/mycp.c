#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<unistd.h>

int main(int argc, char *argv[])
{
    int fptr1, fptr2;
    char str[100];

    fptr1 = open (argv[1], O_RDONLY);
    fptr2 = open (argv[2], O_TRUNC | O_WRONLY | O_CREAT); //O_TRUNC e golit fisierul

    if(fptr1 == -1)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    struct stat stbuf;
    //stat(argv[1], &stbuf); stat preia numele fisierului
    if(stat(argv[1], &stbuf))
    {
        perror("File 1\n"); //intoarce -1 daca e eroare
        return errno;
    }

    read (fptr1, str, stbuf.st_size);
    write (fptr2, str, stbuf.st_size);

    close (fptr1);
    close (fptr2);

    return 0;
}