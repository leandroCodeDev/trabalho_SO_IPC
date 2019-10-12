// Compilar com:
// gcc -pthread thread2.c -o thread2

//consumidor
//usar pthreads para criar vários consumidores

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);
int run_now = 1;
char message[] = "Alo mundo!";

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
    int print_count1 = 0;

    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (res != 0) {
        perror("Criacao de Thread falhou");
        exit(EXIT_FAILURE);
    }

    while(print_count1++ < 20) {
        if (run_now == 1) {
            printf("1");
            run_now = 2;
        }
        else {
            sleep(1);
        }
    }

    printf("\nEsperando por thread finalizar...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread falhou no join");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined\n");
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    int print_count2 = 0;

    while(print_count2++ < 20) {
        if (run_now == 2) {
            printf("2");
            run_now = 1;
        }
        else {
            sleep(1);
        }
    }

    sleep(3);
}
