#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

//parallel funtions
void* busy_wait_calculation(void* rank);
void* mutex_calculation(void* rank);
void* semaphore_calculation(void* rank);

//sequential functions
double f(double x);

//global constants
const int MAX_THREADS = 8;

//global variables
long long a, b, n;
long flag;
double h, approximation;
pthread_mutex_t mutex;
sem_t sema;




int main(void)
{
    double f_a, f_b;
    //char* equation;
    long thread;
    pthread_t* threads;

    flag = 0;
    threads = (pthread_t*) malloc(MAX_THREADS * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sema, 0, 1); //set to one (unlocked)

    //equation = malloc(256); //allocate memory
    //printf("Enter the equation to integrate: ");
    //fgets(equation, 256, stdin); //used to read a string from the console
    printf("Enter a value for a: ");
    scanf("%lld", &a);
    printf("Enter a value for b: ");
    scanf("%lld", &b);
    printf("Enter a value for n: ");
    scanf("%lld", &n);

    //printf("%s", equation); 
    //printf("Values are: a = %lld, b = %lld, n = %lld.\n", a, b, n);

    h = (double)(b - a) / (double)n; //find step size
    f_a = f(a);
    f_b = f(b);

    //busy-wait
    approximation = (f_a + f_b) / 2.0;

    //printf("Busy-Wait\n");
    for(thread = 0; thread < MAX_THREADS; ++thread)
    {
        pthread_create(&threads[thread], NULL, busy_wait_calculation, (void*)thread);
    }
    
    for(thread = 0; thread < MAX_THREADS; ++thread)
    {
        pthread_join(threads[thread], NULL);
    }
    approximation *= h;

    printf("Busy-Wait: approximation = %.5lf.\n", approximation);

    //mutex
    approximation = (f_a + f_b) / 2.0;

    //printf("Mutex\n");
    for(thread = 0; thread < MAX_THREADS; ++thread)
    {
        pthread_create(&threads[thread], NULL, mutex_calculation, (void*)thread);
    }
    
    for(thread = 0; thread < MAX_THREADS; ++thread)
    {
        pthread_join(threads[thread], NULL);
    }
    approximation *= h;

    printf("Mutex: approximation = %.5lf.\n", approximation);

    //semaphore
    approximation = (f_a + f_b) / 2.0;

    //printf("Semaphore\n");
    for(thread = 0; thread < MAX_THREADS; ++thread)
    {
        pthread_create(&threads[thread], NULL, semaphore_calculation, (void*)thread);
    }
    
    for(thread = 0; thread < MAX_THREADS; ++thread)
    {
        pthread_join(threads[thread], NULL);
    }
    approximation *= h;

    printf("Semaphore: approximation = %.5lf.\n", approximation);

    //free allocated memory    
    //free(equation); 
    free(threads);
    sem_destroy(&sema);

    return 0;
}

double f(double x)
{
    double result;
    result = x * x;
    return result;
}

void* busy_wait_calculation(void* rank)
{
    long thread_rank = (long) rank;
    double thread_approx, x_i;
    long long start, end, i;

    thread_approx = 0;
    start = (long)(thread_rank * n / MAX_THREADS);
    end = (long)(((thread_rank + 1) * n / MAX_THREADS) - 1);

    for(i = start; i < end; ++i)
    {
        x_i = a + i * h;
        thread_approx += f(x_i);
    }
    while(flag != thread_rank); //busy-wait loop
    //printf("thread_rank = %ld, start = %lld, end = %lld, flag = %ld \n", thread_rank, start, end, flag);
    //printf("thread_approx = %.5lf, approximation = %.5lf \n", thread_approx, approximation);
    approximation += thread_approx;
    ++flag;
}

void* mutex_calculation(void* rank)
{
    long thread_rank = (long) rank;
    double thread_approx, x_i;
    long long start, end, i;

    thread_approx = 0;
    start = (long)(thread_rank * n / MAX_THREADS);
    end = (long)(((thread_rank + 1) * n / MAX_THREADS) - 1);

    for(i = start; i < end; ++i)
    {
        x_i = a + i * h;
        thread_approx += f(x_i);
    }
    pthread_mutex_lock(&mutex);
    //printf("thread_rank = %ld, start = %lld, end = %lld, flag = %ld \n", thread_rank, start, end, flag);
    //printf("thread_approx = %.5lf, approximation = %.5lf \n", thread_approx, approximation);
    approximation += thread_approx;
    pthread_mutex_unlock(&mutex);
}

void* semaphore_calculation(void* rank)
{
    long thread_rank = (long) rank;
    double thread_approx, x_i;
    long long start, end, i;

    thread_approx = 0;
    start = (long)(thread_rank * n / MAX_THREADS);
    end = (long)(((thread_rank + 1) * n / MAX_THREADS) - 1);

    for(i = start; i < end; ++i)
    {
        x_i = a + i * h;
        thread_approx += f(x_i);
    }
    sem_wait(&sema);
    //printf("thread_rank = %ld, start = %lld, end = %lld, flag = %ld \n", thread_rank, start, end, flag);
    //printf("thread_approx = %.5lf, approximation = %.5lf \n", thread_approx, approximation);
    approximation += thread_approx;
    sem_post(&sema);
}

