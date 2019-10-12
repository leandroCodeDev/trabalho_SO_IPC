
// Compilar com:
// gcc -pthread thread1.c -o thread1
// ./thread1
//criar espaço de memoria compartilhada para salvar um vetor do tipo musica
//criar mutex e talveis semafaros e contador.
// criar uma teste de produtor, para realizar os cadastro automaticos e deixar um
//plano be para entrada de valores.
//e apos disse criar um consumidor para somente realizar a leutura dos dados com slep de 3 sec
// para verificar a rdem de inserção e quem adicionou a musica para garantir o paralelismo
// e apois isso concluido criar os consumidores.

//obs: verificar como professor quer o dados pois pediu comando grep se é pra realizar algo parecido ou realmente usar o 
//grep



// Focar em fazer comunicação entre threads de produtor para escrever na memória compartilhada
    // (só um pode escrever por vez)
// quando estiver escrevendo, consumidores não podem ler
// limitar numero de leituras que os consumidores podem fazer (3 por vez)
// QUando ler, dar um sleep para soh dps poder ler denovo.


//todo Permitir o cadastro de itens (músicas)

//Deve manter várias threads que são usadas para cadastrar musicas.
// Essas threads têm uma memória compartilhada

// vai consumindo essa lista para criar músicas e botar na

//estrutura das músicas nome, Autor, Duração e gênero, tudo string
//https://github.com/vieiralucas/faculdade/tree/master/quarta%20fase/sistemas%20operacionais
//(*** deve ser multithreaded)

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct Musica
{
    char nome[256];
    char autor[256];
    char duracao[256];
    char genero[256];
} Musica;

//funções

void *thread_function(void *arg);

char message[] = "Alo mundo!";

Musica musicas [] = {
    {.nome = "Coding Hard!!!", .autor = "Markinho Zuquis", .duracao = "1:06:66", .genero = "Indie"},
    {.nome = "Coding Hard 2!!!", .autor = "Markinho Zuquis", .duracao = "1:06:66", .genero = "Indie"},
    {.nome = "Coding Hard 3!!!", .autor = "Markinho Zuquis", .duracao = "1:06:66", .genero = "Rock"},
    {.nome = "Coding Hard 4!!!", .autor = "Markinho Zuquis", .duracao = "1:06:66", .genero = "Indie"},
    {.nome = "Coding Hard 5!!!", .autor = "Markinho Zuquis", .duracao = "1:06:66", .genero = "Rock"},
    {.nome = "Coding Hard De volta para casa!!!", .autor = "Markinho Zuquis", .duracao = "1:06:66", .genero = "Indie"},
    {.nome = "Coding Hard e um casamento muito loko!!!", .autor = "Markinho Zuquis", .duracao = "1:06:66", .genero = "Indie"},
    {.nome = "Coding Hard!!!", .autor = "Markinho2 Zuquis", .duracao = "2:06:66", .genero = "Indie"},
    {.nome = "Coding Hard 6!!!", .autor = "Markinho Zuquis", .duracao = "1:06:66", .genero = "Indie"},
    {.nome = "Coding Hard 7!!!", .autor = "Markinho Zuquis", .duracao = "1:06:66", .genero = "Indie"},
    {.nome = "Coding Hard 8!!!", .autor = "Markinho Zuquis", .duracao = "1:06:66", .genero = "Indie"},
    {.nome = "Coding Hard!!!", .autor = "Markinho44 Zuquis", .duracao = "4:06:66", .genero = "Indiee"}
};

int main()
{
    
    int a_res;
    int b_res;
    int c_res;
    int res;
    pthread_t a_thread;
    pthread_t b_thread;
    pthread_t c_thread;
    void *thread_a_result;
    void *thread_b_result;
    void *thread_c_result;

    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (res != 0)
    {
        perror("Criacao de Thread falhou");
        exit(EXIT_FAILURE);
    }
    printf("Esperando por thread finalizar...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0)
    {
        perror("Thread falhou no join");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined, retornou %s\n", (char *)thread_result);
    printf("Mensagem agora eh %s\n", message);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
    printf("thread_function executando. Argumento foi %s\n", (char *)arg);
    sleep(3);
    strcpy(message, "Tchau!");
    pthread_exit("Obrigado pelo tempo de CPU");
}
