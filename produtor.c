
// Compilar com:
// gcc -pthread thread1.c -o thread1
// ./thread1


//todo Permitir o cadastro de itens (músicas) 

//Deve manter várias threads que são usadas para cadastrar musicas. (a partir de uma lista predefina)

// vai consumindo essa lista para criar músicas e botar na

//estrutura das músicas nome, Autor, Duração e gênero, tudo string
//https://github.com/vieiralucas/faculdade/tree/master/quarta%20fase/sistemas%20operacionais
//(*** deve ser multithreaded)

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_function(void *arg);

char message[] = "Alo mundo!";

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (res != 0) {
        perror("Criacao de Thread falhou");
        exit(EXIT_FAILURE);
    }
    printf("Esperando por thread finalizar...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread falhou no join");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined, retornou %s\n", (char *)thread_result);
    printf("Mensagem agora eh %s\n", message);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    printf("thread_function executando. Argumento foi %s\n", (char *)arg);
    sleep(3);
    strcpy(message, "Tchau!");
    pthread_exit("Obrigado pelo tempo de CPU");
}
