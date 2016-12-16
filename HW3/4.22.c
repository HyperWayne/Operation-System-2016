#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int i = 0;	
int amountOfPoints = 0;
int totalPoints = 0;

void* count(void *X)
{ 
    for (i=0; i < amountOfPoints; i++)
    {	
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;
      	
	/** X and Y will be randomed in the range of 0~1 (square)   
         *
	 *  If X and Y are in the circle
	 *
	 *  Let the global variable records it
	 */

	if (((X * X) + (Y * Y)) <= 1)
        {
	   // global variables
           totalPoints++;
        }
    }
    return NULL;
}

int main()
{
    printf("Monte Carlo method for calculating PI (multi thread)\n");
    srand(time(NULL));
    pthread_t thread; 

    do{
        printf("Amount of random Points : \n");  // here's the input
        scanf("%d", &amountOfPoints);  	
    }while (amountOfPoints <= 0);
  
    // single thread
    pthread_create(&thread, NULL, &count, NULL);
    pthread_join(thread, NULL);
    
    double points = 4.0 * totalPoints;
    double pi = points / amountOfPoints;
    printf("The approximating value of pi for the amount of points (%d) is: %f\n\n", amountOfPoints, pi);  
   
    return 0;
}
