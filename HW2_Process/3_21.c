#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Unix Standard
#include <sys/wait.h>

int main(int agrc, char * agrv[])
{
  if(agrc!=2){ 
  
  	printf("Command Error\n"); 
	printf("Try ./3_21 [A Positive interger]\n");
	return 0;
  }

  pid_t pid; // Process Identifier

  pid = fork(); // fork another process

  /**
   *	Parent Process return 1	(init Process)
   *	Child  Process return 0
   * **/

  if(pid<0){ // error occurred
  	
  	printf("** Fork Failed ** \n");
	exit(-1);
  }
  
  else if(pid==0){ // child process
  
  	printf("** Child Process **\n");	
	
	/* Implement the Algorithm */	
	int n = atoi(agrv[1]);	printf("%d",n);
	while(n!=1){  /* if n is even , n/2, else if odd 3*n+1 */
	    n = (n%2) ? (3*n+1) : n/2 ;
	    printf(", %d",n); 
	} printf("\n");
  	printf("** Child ends **\n");
  }

  else{ // parent process
  	wait(NULL); 
	printf("** Parent ends **\n");
  	exit(0);
  }

  return 0;
}
