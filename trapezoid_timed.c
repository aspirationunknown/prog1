#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//parallel funtions
void* semaphore_calculation(void* rank);

//sequential functions
double f(double x);

//global constants
const int MAX_THREADS = 8;

//global variables
long long a, b, n;
long flag;
double h, approximation;
sem_t sema;




int main(void)
{
    struct timeval begin, end;
    double f_a, f_b;
    //char* equation;
    long thread;
    pthread_t* threads;
    double total_time;

    flag = 0;
    threads = (pthread_t*) malloc(MAX_THREADS * sizeof(pthread_t));
    total_time = 0;
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

    gettimeofday(&begin, NULL);

    h = (double)(b - a) / (double)n; //find step size
    f_a = f(a);
    f_b = f(b);

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

    gettimeofday(&end, NULL);
    total_time = (double)((end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec))/ 1000000.0;
    printf("Semaphore: approximation = %.5lf, time elapsed = %.10lf seconds.\n", approximation, total_time);

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

