// Compilar com:
// gcc -pthread thread3.c -o thread3

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 6

void *thread_function(void *arg);

int main() {
    int res;
    pthread_t a_thread[NUM_THREADS];
    void *thread_result;
    int lots_of_threads;

    for(lots_of_threads = 0; lots_of_threads < NUM_THREADS; lots_of_threads++) {

        res = pthread_create(&(a_thread[lots_of_threads]), NULL, thread_function, (void *)&lots_of_threads);
        if (res != 0) {
            perror("Criacao de Thread falhou");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }
    printf("Esperando por thread finalizar...\n");
    for(lots_of_threads = NUM_THREADS - 1; lots_of_threads >= 0; lots_of_threads--) {
        res = pthread_join(a_thread[lots_of_threads], &thread_result);
        if (res == 0) {
            printf("Pegou uma thread\n");
        }
        else {
            perror("Thread falhou no join");
        }
    }
    printf("Todas terminaram\n");
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    int my_number = *(int *)arg;
    int rand_num;

    printf("thread_function executando. Argumento foi %i\n", my_number);
    
    rand_num=1+(int)(9.0*rand()/(RAND_MAX+1.0));
    sleep(rand_num);
    printf("Adeus da thread %d\n", my_number);
    pthread_exit(NULL);
}
