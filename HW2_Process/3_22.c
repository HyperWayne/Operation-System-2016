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

  const char *name = "shm_obj";  /*name for shared memory object */

  const int size = 4096; /* size for shared memory object */
  
 
  /* CREATE/OPEN POSIX shared memory object */
 
  int fd = shm_open(name, O_CREAT| O_RDWR, S_IRUSR | S_IWUSR);
   if(fd == -1){
	printf("** share memory failed **\n"); 	exit(-1);
  }

  /* set the memory object's size */
  
  int r = ftruncate(fd, size);
   if(r != 0){
	printf("** ftruncate error **\n");  exit(-1);
  }
  
  /* Map the memory object */
  
  void *ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   if( ptr == MAP_FAILED){
	printf("** Map Error **\n");  exit(-1);
  }
 
  close(fd);
 


  /**
   *	Parent Process return 1	(init Process)
   *	Child  Process return 0
   *
   * **/

  pid = fork(); // fork another process
  
  /* create the child process and wait for it to terminate  */

  if(pid<0){ // error occurred
  	
  	printf("** Fork Failed ** \n");
	exit(-1);
  }
  
  else if(pid==0){ // child process
  
  	printf("** Child Process **\n");	
	
	/* Implement the Algorithm */	
	int n = atoi(agrv[1]);	//printf("%d",n);
	int shrd_resc[size] , index = 0;

	while(n!=1){  /* if n is even , n/2, else if odd 3*n+1 */
	    shrd_resc[index++] = n;
	    n = (n%2) ? (3*n+1) : n/2 ;
	} shrd_resc[index++] = 1;
  
				  
	//printf("** Child is dealing with the algorithm. **\n");

	int i;
	
	for(i = 0; i<index; i++){
		sprintf((char *)ptr, "%d", shrd_resc[i]);
	 	/* Since we use the type 'char' to store, and we assume the number should not exceed 10 digit */
		ptr += 10*sizeof(char);
	}
	
	printf("** Child ends **\n");

	exit(0);
  }

  else{ // parent process
  
	wait(NULL); /* wait for the child */

	/* read from the shared memory object */	

	char *string = (char *)ptr;
	printf("%s", string);

	/* output the contents of shared memory */

	while(!(strcmp(string, "1")==0)){

		ptr += 10*sizeof(char);
		string = (char *) ptr;
		printf(", %s", string);
	}

	printf("\n** Parent ends **\n");

	/* Removed the shared-memory object */
	r = shm_unlink(name);
	if(r != 0){
		printf("** shm_unlink Error **\n");
		exit(-1);
	}
  	exit(0);
  }

  return 0;
}
