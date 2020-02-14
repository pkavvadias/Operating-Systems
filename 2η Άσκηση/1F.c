#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define N 3 //plh8os diergasiwn

typedef sem_t Semaphore;
Semaphore *mutex;  

int randomInt(int lower,int upper) 
{ 
	int num = (rand() %(upper - lower + 1)) + lower; 
	return(num); 
}
  
int main()
{
	pid_t pid;   //pinakas paidiwn 
	int i=0;            //counter
	char *t;	    //temp pointer
	char temp[255]="";  //temp string for strcat()
	char *p;	    //shared memory
	key_t shmkey;       // shared memory key         
	int shmid;          // shared memory id          
	int child_status;   //for father
	int rendom;
	int nSeconds[N];

	system("clear");

	t= temp;
	
	for(int l=0; l<N; l++) // random number array
	{
		nSeconds[l] = randomInt(1,5);
	}	

	mutex = sem_open ("pSem", O_CREAT | O_EXCL, 0644, 1);//open mutex

	if (shmid < 0)       //if error exit                    
	{
		perror ("shmget\n");
		exit (1);
	}

	for (int i=0; i<N; i++) // dhmiourgia diergasiwn 
	{
		pid=fork();

		if (pid < 0) { //if error
            sem_unlink ("pSem");   
            sem_close(mutex);  
			printf ("Fork error.\n");
		}
		else if(pid==0) //if child
		{
			break;		
		}
		//printf("pid[%i] = %i\n", i, pid[i]);
	}

	if (pid > 0) //if parent
	{
        	// wait for all children to exit 
        	while (pid == waitpid (-1, NULL, 0))
        	{
            		if (errno == ECHILD)
                	break;
       		}

		printf (" Parent: All children have exited.\n");
			printf (" *p = %d\n\n", *p);
			

		shmdt (p);
		shmctl (shmid, IPC_RMID, 0);


		sem_unlink ("pSem");   
		sem_close(mutex);  //close mutex
	}

	else
	{
	    sem_wait (mutex);           //down(mutex)

		printf (" Child(%d) enters the critical section.\n", i);
		printf (" Waiting %d seconds.\n", nSeconds[i]);
		
		sleep(nSeconds[i]);       //sleep
		printf("Enter text\n");

		char c=getchar();         //clean buffer
		scanf("%[^\n]s",temp);    //scan text
		t=p;                      //temp pioter with new text

		strcat(t,temp);           //concatenating new text to t
		p=t;                      //set *p  to point to the full text
		*p=*t;

		
		printf (" Child(%d) exits the critical region\n", i);
		printf (" new value of *p=%s.\n\n\n", p);

		sem_post(mutex);           //up(mutex)
	}

return(0);
}
