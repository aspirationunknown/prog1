#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

double f(double x);

//global constants
const int NUM_THREADS = 4;
//global variables
pthread_mutex_t mutex;



int main(void)
{
    double a, b, f_a, f_b, h, n, x_i;
    double approximation;
    char* equation;
    long i, thread;
    pthread_t* threads;

    threads = (pthread*) malloc(NUM_THREADS * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);

    equation = malloc(256); //allocate memory
    printf("Enter the equation to integrate: ");
    fgets(equation, 256, stdin); //used to read a string from the console
    printf("Enter a value for a: ");
    scanf("%lf", &a);
    printf("\nEnter a value for b: ");
    scanf("%lf", &b);
    printf("\nEnter a value for n: ");
    scanf("%lf", &n);

    printf("%s", equation);
    //f = inline(equation, 'x'); 
    printf("Values are: a = %.3lf, b = %.3lf, n = %.0lf.\n", a, b, n);

    h = (b - a) / n; //find step size
    f_a = f(a);
    f_b = f(b);
    approximation = (f_a + f_b) / 2.0;

    for(i = 0; i < n - 1; ++i)
    {
        x_i = a + i * h;
        approximation += f(x_i);
    }

    approximation *= h;

    printf("Values are: a = %.3lf, b = %.3lf, n = %.0lf, approximation = %.3lf.\n", a, b, n, approximation);
    
    free(equation); //free allocated memory

    return 0;
}

double f(double x)
{
    double result;
    result = x * x + 3;
    return result;
}
