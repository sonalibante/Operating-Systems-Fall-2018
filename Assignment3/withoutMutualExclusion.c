#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define TIMES 10
#define CAPACITY 3
#define ITEMSIZE 20

void *threadA();
void *threadB();
void *threadC();

float funds = 4000.00;
float fundsused = 0;

int main()
{
    int i;
    pthread_t tid;

    pthread_setconcurrency(2);

    while(funds > 0){
        pthread_create(&tid, NULL, (void *(*)(void *))threadA, NULL  );
        pthread_create(&tid, NULL, (void *(*)(void *))threadB, NULL );
        pthread_create(&tid, NULL, (void *(*)(void *))threadC, NULL );
    }

    pthread_exit(0);

}

//Without Mutual Exclusion
void *threadA(){
    float calc;
    calc = ceil(funds * 0.25);
    funds = funds - calc;
    fundsused += calc;

    printf("A : %.0f \n", calc);
}

//Without Mutual Exclusion
void *threadB(){
    float calc;
    calc = ceil(funds * 0.25);
    funds = funds - calc;
    fundsused += calc;

    printf("B : %.0f \n", calc);
}

//Without Mutual Exclusion
void *threadC(){
        float calc;
        calc = ceil(funds * 0.25);
        funds = funds - calc;
        fundsused += calc;

        printf("C : %.0f \n", calc);
}

