#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pid;
    int x,y;
    
    x = 10;
    y = 10;
    
    pid = fork();

    
    if (pid != 0)
    {
	   x++;
       y--;
    }
    
    printf("getpid() = %i \t , getppid() = %i, pid=%i, if 1\n",getpid(), getppid(), pid); //print getpid(),getppid and pid for first print(x,y)
    printf("x = %i y = %i\n",x,y);
    printf("\n");
    
    pid = fork();
    
    
    if (pid != 0)
    {
       x++;
       y--;
    }

    printf("getpid() = %i \t , getppid() = %i, pid=%i, if 2\n",getpid(), getppid(), pid); //print getpid(),getppid and pid for second print(x,y)

    printf("x = %i y = %i\n",x,y);
    printf("\n");
   
    return (0);
}