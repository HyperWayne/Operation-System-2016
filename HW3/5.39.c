#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int i = 0;	
int amountOfPoints = 0;
int totalPoints  = 0;
int all = 0;

pthread_t tid[2];
pthread_mutex_t lock;

void *count(void *X)
{
    // mutex lock
    // Protect against race conditions on updates to the shared global variable by using mutex locks
    pthread_mutex_lock(&lock);
    
    all = all + amountOfPoints;
   
    // Same idea with problem 4.22 and 4.23 here 
    for (i=0; i < amountOfPoints; i++)
    {	
        double X = (double)rand() / RAND_MAX;
	double Y = (double)rand() / RAND_MAX;
        
        if (((X * X) + (Y * Y)) <= 1)
        {
            totalPoints++;
        }
    }
   
    // mutex lock
    pthread_mutex_unlock(&lock);
    return;
}

int main()
{
    printf("Monte Carlo method for calculating PI(mutex lock)\n");
    srand(time(NULL));

    do{
        printf("Amount of random Points : \n"); // here's the input
        scanf("%d", &amountOfPoints);  	
    }while (amountOfPoints <= 0);
  
    //make sure the lock is initialized correctly
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    //try with two threads
    pthread_create(&(tid[0]), NULL, &count, NULL);
    pthread_create(&(tid[1]), NULL, &count, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);
    
    double points = 4.0 * totalPoints;
    double pi = points / all;
    printf("The approximating value of pi for the amount of points (%d) is: %f\n\n", amountOfPoints, pi);  
    return 0;
}
