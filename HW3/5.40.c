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

printf("Monte Carlo method for calculating PI(openmp with critical section)\n");
srand(time(NULL));
    
do
{
    printf("Amount of random Points : \n");
    scanf("%d", &amountOfPoints);
}while (amountOfPoints <= 0);

// Most are the same as in 4.23 , however, we protect the resources by critical section
#pragma omp parallel
{
    int i;
    #pragma omp for
    for (i=0; i < amountOfPoints; i++)
    {	
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;
        
        if (((X * X) + (Y * Y)) <= 1)
        {
            #pragma omp critical  // Protection
            totalPoints++;
        }
    }
}
    

double points = 4.0 * totalPoints;
double pi = points / amountOfPoints;
printf("The approximating value of pi for the amount of points (%d) is: %f\n\n", amountOfPoints, pi);  
return 0;
}
