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

typedef sem_t Semaphore;
Semaphore *sem_1; //first semaphore for 1/2-->4 progresses
Semaphore *sem_2; //second semaphore for 4/3-->5progresses
	
int main()
{
	pid_t pid[5]={0}; //array for progresses
	int i=0; //counter
	int child_status; //for parent
	system("clear");  //clear
	
	sem_1=sem_open("Sem1",O_CREAT | O_EXCL, 0644,0); //open sem1
	sem_2=sem_open("Sem2",O_CREAT | O_EXCL, 0644,0); //open sem2

	for (int i=0; i<5; i++) //dhmiourgia diergasiwn
	{
		pid[i]=fork(); 
		if(pid[i]==0)
		{
			break;		
		}
		//printf("pid[%i] = %i\n", i, pid[i]);
	}

	if(pid[0]==0)  //1h diergasia
	{
		printf("First Progress:\n");			
		system("ls -l");   //emfanish arxeiwn
		printf("\n\n");
		sem_post(sem_1);   //up(sem1)
	}

	if(pid[0]!=0 && pid[1]==0) //2h diergasia
	{
		printf("Second Progress:\n");		
		system("pwd"); //trexwn fakelos ergasias
		printf("\n\n");
		sem_post(sem_1); //up(sem1)
	}

	if(pid[0]!=0 && pid[1]!=0 && pid[2] ==0) //3h diergasia
	{
		printf("Third Progress:\n");		
		system("ps -l"); //trexouses diergasies
		printf("\n\n");
		sem_post(sem_2); //up(sem2)
	}

	if(pid[0]!=0 && pid[1]!=0 && pid[2]!=0 && pid[3]==0) //4h diergasia
	{
		sem_wait(sem_1); //down(sem1)
		sem_wait(sem_1); //down(sem1)
		printf("Fourth Progress:\n");		
		system("pwd");   //trexwn fakelos ergasias
		printf("\n\n");
		sem_post(sem_2); //up(sem2)
	}

	if(pid[0]!=0 && pid[1]!=0 && pid[2]!=0 && pid[3]!=0 && pid[4]==0) //5h diergasia
	{
		sem_wait(sem_2);
		sem_wait(sem_2);
		printf("Fifth Progress:\n");		
		system("tree");
		printf("\n\n");	
		//printf("End of programm");		
	}

	if(pid[0]!=0 && pid[1]!=0 && pid[2]!=0 && pid[3]!=0 && pid[4]!=0) //parent
	{
		for (i = 0; i < 4; i++)
		{
			pid_t wpid = waitpid(pid[i], &child_status, 0);
		}

		sem_unlink ("Sem1");   
		sem_close(sem_1);  
		sem_unlink ("Sem2");   
		sem_close(sem_2);  
	}

return(0);
}