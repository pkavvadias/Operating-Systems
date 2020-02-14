#include <stdio.h>
#include <stdlib.h>

int main()
{
	int pid;
	for(int i=0; i=3; i++)
	pid = fork();                   //dhmiourgia diergasiwn
		printf("pid = %i\n",pid);   //print pid
		if (pid == 0)               //if pid=child
		{
			printf("The child (Id=%i) have ", getpid() );
			printf("parent with id: %i\n\n", getppid() );
		}
		else                        //if pid=parent
		{
			printf("The parent (Id=%i) have ", getpid() );
			printf("a child with id: %i\n\n", pid );
		}
	}

    return (0);
}