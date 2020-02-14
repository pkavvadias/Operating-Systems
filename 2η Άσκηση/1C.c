#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int pid;
	int status;
	printf("The parent (Id=%i) has a child with id: %i\n", getppid(), getpid() ); //for parent procces
        
	for (int i=0; i<4; i++)
	{
		pid = fork();     //dhmiourgia diergasiwn
		if (pid == 0)     //if child
		{
			printf("The child (Id=%i) has ", getpid() );
			printf("parent with id: %i\n", getppid() );
		}
		else
		{
			printf("The parent (Id=%i) has ", getpid() );
			printf("a child with id: %i\n", pid );
			wait(&status);
			break;      //if father break

		}
	}

    return (0);
}