 #include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

void collatz (int *buffer, int x){
	buffer[0]=x;
	int last=1;
	while(x!=1){
		if (x%2==0){
			x=x/2;
		}
		else{
			x=x*3+1;
		}
		buffer[last]=x;
		last++;
	}
	buffer[last]=1;
	return;
}

void afisare(int *buffer)
{
	int i=0;
	printf("%d:",buffer[i]);
	while (buffer[i]!=1)
	{
		printf("%d ",buffer[i]);
		i++;
	}
	printf("1");
	printf("\n");
}

int main (int argc, const char *argv[])
{
	char shm_name[] = "/collatz";
	int shm_fd;///putem sa il folosim pentru manipularea ob
	///creare obiect de memorie partajata
	shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	if (shm_fd<0)
	{
		perror(NULL);
		return errno;
	}

	size_t shm_size = 1024 * argc;
	//definim dimensiunea cu ftruncate
	if (ftruncate(shm_fd, shm_size) == -1)
	{
	//ftruncate mareste/scurteaza cf dimensiunii din al 2lea argument
		perror(NULL);
		///sterge obiectele create cu functia shm_open
		shm_unlink(shm_name);
		return errno;
	}
	///afisez id-ul parintelui
	printf("Starting parent %d\n",getpid());
	///pentru fiecare argument
	for (int i=1; i<argc; i++)
	{
		int x = atoi(argv[i]); //fac conversia la int
		pid_t pid=fork();///creez proces
		if (pid<0)
		{
			return errno;
		}
		else{
			if (pid==0)///daca este copil
			{
	///addr va fi un pointer catre adresa la care a fost incarcat obiectul
	///in cazul in care se executa cu succes
	int *addr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
				///altfel
				if (addr == MAP_FAILED)
				{
					perror(NULL);
					shm_unlink(shm_name);///sterg ob create
					return errno;
				}
				int *buffer = addr+(i-1)*1024/sizeof(int);
				///sare peste cele 1024 de spatii de dinainte
				collatz(buffer,x);
				printf("Done Parent %d Me %d\n", getppid(), getpid());
				return 0;
			}
	}
}
	while(wait(NULL) > 0);///asteapta toti copiii
	int *addr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	for (int i=1; i<argc; i++)
	{
		afisare(addr+(i-1)*1024/sizeof(int));
	}
	munmap(addr, shm_size);///eliberam zona de memorie incarcata anterior
	shm_unlink("/collatz");
	return 0;
}

