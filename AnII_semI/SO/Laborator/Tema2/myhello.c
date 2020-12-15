#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<unistd.h>

int main(int argc, char *argv[])
{
    int fptr;
    fptr = open(argv[1], O_RDONLY);

    if(fptr == -1)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    struct stat stbuf;
    stat(argv[1], &stbuf);
    char str[stbuf.st_size + 1];

    read(fptr, str, stbuf.st_size);
    str[stbuf.st_size]= '\0';
    printf(str, '\n');

    return 0;
    
    //alternativ
    write(1, "Hello, World!\n", 13 );
    
}
