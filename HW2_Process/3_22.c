#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Unix Standard
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>


int main(int agrc, char * agrv[])
{
  if(agrc!=2){ 
  
  	printf("Command Error\n"); 
	printf("Try ./3_22 [A Positive interger]\n");
	return 0;
  }

  pid_t pid; // Process Identifier

  pid = fork(); // fork another process

  /**
   *	Parent Process return 1	(init Process)
   *	Child  Process return 0
   *
   * **/

  const char *name = "3_22";  /*name for shared memory object */
  
  const int size = 4096; /* size for shared memory object */
  

  if(pid<0){ // error occurred
  	
  	printf("** Fork Failed ** \n");
	exit(-1);
  }
  
  else if(pid==0){ // child process
  
  	printf("** Child Process **\n");	
	
	/* Implement the Algorithm */	
	int n = atoi(agrv[1]);	//printf("%d",n);
	int shrd_resc[size] , index = 0;
	void *ptr;	

	while(n!=1){  /* if n is even , n/2, else if odd 3*n+1 */
	    shrd_resc[index++] = n;
	    n = (n%2) ? (3*n+1) : n/2 ;
	} shrd_resc[index++] = 1;
  
	int fd = shm_open(name, O_RDWR|O_CREAT, 6666);  /* create/open POSIX shared memory object */
				  
	/* set the memory object's size */
			
	ftruncate(fd, size);  

 	/* Map the memory object */
        ptr =  mmap(0, size, PROT_WRITE,
			 MAP_SHARED, fd, 0);
	
	//printf("** Child is dealing with the algorithm. **\n");

	int i;
	
	for(i = 0; i<index; i++){
		sprintf(ptr, "%d", shrd_resc[i]);
	 	/* Since we use the type 'char' to store, and we assume the number should not exceed 10 digit */
		ptr += 10*sizeof(char);
	}
	
	printf("** Child ends **\n");
  }

  else{ // parent process
  
	wait(NULL); /* wait for the child */

  	int fd = shm_open(name, O_RDONLY, 6666); /* 6666 for port number*/

	if(fd == -1){ 
		printf("** shared memory failed. **\n");
		exit(-1);
	}

	void *ptr;	
	ptr = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);

	// printf("Parent is waiting for child to complete ... \n");
	
	/* read from the shared memory object */	

	char *output; 

	output = (char *)ptr;
	printf("%s", output);

	while(!(strcmp(output, "1")==0)){
		ptr += 10*sizeof(char);
		output = (char *) ptr;
		printf(", %s", output);
	}

	printf("\n** Parent ends **\n");
  	exit(0);
  }

  return 0;
}
