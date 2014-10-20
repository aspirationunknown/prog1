#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//global constants
const long NUM_PHILOSOPHERS = 5;

//global variables
pthread_mutex_t chopstick_mutex[5];

void* grab_chopsticks(void* rank);


int main(void)
{
    long i, j;
    pthread_t* threads = (pthread_t*)malloc(NUM_PHILOSOPHERS * sizeof(pthread_t));
;

    for(i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        pthread_mutex_init(&chopstick_mutex[i], NULL);
        printf("Philosopher %d is thinking.\n", i);
    }

    for(j = 0; j < 10; ++j)
    {
        for(i = 0; i < NUM_PHILOSOPHERS; ++i)
        {
            pthread_create(&threads[i], NULL, grab_chopsticks, (void*)i);
        }

        for(i = 0; i < NUM_PHILOSOPHERS; ++i)
        {
             pthread_join(threads[i], NULL);
        }
    }

    free(threads);
    

    return 0;
}


void* grab_chopsticks(void* rank)
{
    long thread_rank = (long)rank;

    pthread_mutex_lock(&chopstick_mutex[thread_rank]);
    printf("Philosopher %ld picked up chopstick %ld.\n", thread_rank, thread_rank);
    pthread_mutex_lock(&chopstick_mutex[(thread_rank + 1) % NUM_PHILOSOPHERS]);
    printf("Philosopher %ld picked up chopstick %ld.\n", thread_rank, (thread_rank + 1) % NUM_PHILOSOPHERS);
    printf("Philosopher %ld is eating.\n", thread_rank);
    sleep(5);
    pthread_mutex_unlock(&chopstick_mutex[(thread_rank + 1) % NUM_PHILOSOPHERS]);
    printf("Philosopher %ld put down chopstick %ld.\n", thread_rank, (thread_rank + 1) % NUM_PHILOSOPHERS);
    pthread_mutex_unlock(&chopstick_mutex[thread_rank]);
    printf("Philosopher %ld put down chopstick %ld.\n", thread_rank, thread_rank);
    printf("Philosopher %ld is thinking.\n", thread_rank);
}
