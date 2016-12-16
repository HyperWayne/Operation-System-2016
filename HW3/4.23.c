#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

int amountOfPoints = 0;
int totalPoints  = 0;

int main()
{

printf("Monte Carlo method for calculating PI(openmp)\n");
srand(time(NULL));
    
do
{
    printf("Amount of random Points : \n");  // here's the input
    scanf("%d", &amountOfPoints); 
}while (amountOfPoints <= 0);

// parallel section in openMP
#pragma omp parallel
{
    int i;
   
    #pragma omp for
    for (i=0; i < amountOfPoints; i++)
    {	
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;
        
	/**  X and Y will be randomed in the range of 0~1 (square)
	 *   If X and Y are in the circle
	 *   These points will be recored in global variable
	 * */

        if ((X * X) + (Y * Y) <= 1)
        {
		// global variables
		// There may exist race condition
    		totalPoints++;
        }
    }
}
   
double points = 4.0 * totalPoints;
double pi = points / amountOfPoints;
// use the amount of points saved in totalpoints to calculate PI
// It's an approximation
printf("The approximating value of pi for the amount of points (%d) is: %f\n\n", amountOfPoints, pi);  

return 0;

}



