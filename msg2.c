/* The sender program is very similar to msg1.c. In the main set up, delete the
 msg_to_receive declaration and replace it with buffer[BUFSIZ], remove the message
 queue delete and make the following changes to the running loop.
 We now have a call to msgsnd to send the entered text to the queue. */



// COMPILE COM:      gcc -pthread -o msg2 msg2.c


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/msg.h>

#define MAX_TEXT 2048
#define NUM_THREADS 3
#define TAMANHO_ARRAY_MUSICAS 30

typedef struct Musica
{
    char nome[256];
    char autor[256];
    char duracao[256];
    char genero[256];
} Musica;

Musica musicas [] = {
        {.nome = "Dessert", .autor = "Darwin", .duracao = "3:30", .genero = "POP"},
        {.nome = "O Astronauta de Marmore", .autor = "Nenhum de nos", .duracao = "3:59", .genero = "MPB"},
        {.nome = "Give It All", .autor = "Rise Against", .duracao = "2:50", .genero = "Indie"},
        {.nome = "Should I Stay or Should I Go", .autor = "The Clash", .duracao = "3:08", .genero = "Rock"},
        {.nome = "Carry on Wayward Son", .autor = "Kansas", .duracao = "5:23", .genero = "Rock"},
        {.nome = "Piano Man", .autor = "Billy Joel", .duracao = "5:39", .genero = "Soft Rock"},
        {.nome = "The House of the Rising Sun", .autor = "The Animals", .duracao = "4:29", .genero = "Folk Rock"},
        {.nome = "Let it Be", .autor = "The Beatles", .duracao = "4:03", .genero = "Rock"},
        {.nome = "The sound of silence", .autor = "Simon & Garfunkel", .duracao = "3:05", .genero = "Pop"},
        {.nome = "The sound of silence - Disturbed", .autor = "Disturbed", .duracao = "4:08", .genero = "Metal"},
        {.nome = "I Am Rock", .autor = "Rock", .duracao = "3:50", .genero = "Rock"},
        {.nome = "Valentino", .autor = "24KGoldn", .duracao = "2:59", .genero = "Hip-Hop"},
        {.nome = "You win Again", .autor = "Bee Gees", .duracao = "4:01", .genero = "Classica"},
        {.nome = "Listen to your Heart", .autor = "Roxette", .duracao = "5:28", .genero = "Pop"},
        {.nome = "My Sweet Lord", .autor = "George Harrison", .duracao = "4:41", .genero = "Country"},
        {.nome = "Super Trouper", .autor = "Abba", .duracao = "4:12", .genero = "Pop"},
        {.nome = "I Have A Dream", .autor = "Abba", .duracao = "4:45", .genero = "Pop"},
        {.nome = "Pais e Filhos", .autor = "Legiao Urbana", .duracao = "5:08", .genero = "MPB"},
        {.nome = "I hate u, i lovoe u", .autor = "Olivia O'Brien", .duracao = "4:11", .genero = "Pop"},
        {.nome = "GoodByes", .autor = "Post Malone", .duracao = "2:54", .genero = "Hip-Hop"},
        {.nome = "Drip Different", .autor = "Ebon Lurks", .duracao = "3:18", .genero = "Hip-Hop"},
        {.nome = "Haruka Kanata", .autor = "Asisan Kung-fu generation", .duracao = "4:03", .genero = "Rock"},
        {.nome = "Silhouette", .autor = "Kana-Boon", .duracao = "4:00", .genero = "Pop"},
        {.nome = "I Feel It Coming", .autor = "The Weekend", .duracao = "4:29", .genero = "Pop"},
        {.nome = "Starboy", .autor = "The Weekend", .duracao = "3:50", .genero = "Pop"},
        {.nome = "Violent Pornography", .autor = "System Of A Down", .duracao = "3:31", .genero = "Rock Alternativo"},
        {.nome = "Send Me An Angel", .autor = "Scorpions", .duracao = "4:33", .genero = "Rock Classico"},
        {.nome = "Tonight Tonight", .autor = "Hot Chelle Rae", .duracao = "3:20", .genero = "Pop"},
        {.nome = "Ave Maria", .autor = "Luciano Pavarotti", .duracao = "4:56", .genero = "Classica"},
        {.nome = "I Will Find", .autor = "Vintage Culture", .duracao = "3:44", .genero = "Eletronica"},
        {.nome = "Forever", .autor = "HaroinFather", .duracao = "1:48", .genero = "India"},
        {.nome = "The Less I Know The Better", .autor = "Tame Impala", .duracao = "3:36", .genero = "Pop"}
    };

void *thread_function(void *arg);

int main()
{
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
        } else {
            perror("Thread falhou no join");
        }
    }
    printf("Todas terminaram\n");

    exit(EXIT_SUCCESS);
}



void *thread_function(void *arg) {
    int my_number = *(int *)arg;
    int msgid;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        fprintf(stderr, "msgget falhou na thread %d with error: %d\n", my_number, errno);
        pthread_exit(NULL);
    }

    while (1)
    {
        int indexMusica = rand() % TAMANHO_ARRAY_MUSICAS;
        
        printf("Thread %d produziu a musica no index %d de nome %s\n", my_number, indexMusica, musicas[indexMusica].nome);

        if (msgsnd(msgid, (void *)&musicas[indexMusica], MAX_TEXT, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }

        sleep(5);
        
    }

    pthread_exit(NULL);
}