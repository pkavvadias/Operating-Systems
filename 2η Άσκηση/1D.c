#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 100


int nothing()  //nothing function 
	{
		int x=0;
		x=x+1;
		//printf("x = %i\n", x);
		return(0);
	}

int main()
{
	time_t start; //start sec
	time_t end;   //end sec
	double timeT; //sunolikos xronos
	pid_t parent=getpid(); //foather pid
	
	int k=0;      //counters
	int q=0;

	pid_t pid[N]={0};  //array for progresses
	int child_status;  //for father

	
	time(&start);      //start time
	printf("Arxikh timh deuteroleptwn: %i sec\n", start);

	while(k<N)
	{
		k++;
		if(fork()==0)   //dhmiourgia diergasiwn: if child
		{
			nothing();
			pid[k]=getpid();
			printf("pid[%i] = %i\n", k, pid[k]);
			q=0;
			break;
		}
		else //parent
		{
			q++;
		}
		
	}

	if(getpid()==parent){ //if father
		for(k=0; k<N; k++)
		{
			printf("in %i\n", k);
			pid_t wpid = waitpid(pid[k], &child_status,0); //wait
		}
	}

	if(getpid()==parent){  //if father
		
		time(&end);        //stop time
		printf("telikh timh deuteroleptwn: %i sec\n", end);
		
		timeT = end-start; //run time
		printf("Sunolikos xronos ekteleshs: %i sec\n", timeT);
		
		timeT = timeT/N;   //Avg time
		printf("Mesos xronos ekteleshs: %i sec\n", timeT);
	}
	return(0);	
}