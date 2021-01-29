#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define TIMES 10
#define CAPACITY 3
#define ITEMSIZE 20

void *threadA();
void *threadB();
void *threadC();

pthread_mutex_t mutex;
pthread_cond_t  full_cond;
pthread_cond_t  empty_cond;

float funds = 4000.00;
float fundsused = 0;

int main()
{
    pthread_t tid;

    pthread_setconcurrency(2);

    while(fundsused != 4000.00){
        pthread_create(&tid, NULL, (void *(*)(void *))threadA, NULL  );
        pthread_create(&tid, NULL, (void *(*)(void *))threadB, NULL );
        pthread_create(&tid, NULL, (void *(*)(void *))threadC, NULL );
    }

    printf("Total Given out: %.0f \n \n", fundsused);

    pthread_exit(0);

}

//With Mutual Exclusion
void *threadA(){
    pthread_mutex_lock(&mutex);

    if(funds > 0){
        float calc;
        calc = ceil(funds * 0.25);
        funds = funds - calc;
        fundsused += calc;

        printf("A : %.0f \n", calc);
    }

    pthread_mutex_unlock(&mutex);
}

//With Mutual Exclusion
void *threadB(){
    pthread_mutex_lock(&mutex);

    if(funds > 0){
        float calc;
        calc = ceil(funds * 0.25);
        funds = funds - calc;
        fundsused += calc;

        printf("B : %.0f \n", calc);
    }

    pthread_mutex_unlock(&mutex);
}

//With Mutual Exclusion
void *threadC(){
    pthread_mutex_lock(&mutex);

    if(funds > 0){
        float calc;
        calc = ceil(funds * 0.25);
        funds = funds - calc;
        fundsused += calc;

        printf("C : %.0f \n", calc);
    }

    pthread_mutex_unlock(&mutex);
}

