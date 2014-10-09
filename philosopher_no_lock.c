#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "phil_queue.h"

//Global constant for number of Philosophers
const int NUM_OF_PHILOSOPHERS = 5;

int main(void)
{
    int i;
    Philosopher* philosophers[NUM_OF_PHILOSOPHERS];
    //allocate memory for the philosophers
    for(i = 0; i < NUM_OF_PHILOSOPHERS; ++i)
    {
        philosophers[i] = malloc(sizeof(Philosopher));
    }




    //deallocate memory used for the philosophers
    for(i = 0; i < NUM_OF_PHILOSOPHERS; ++i)
    {
        philosophers[i] = realloc(sizeof(Philosopher));
    }

    return 0;
}
