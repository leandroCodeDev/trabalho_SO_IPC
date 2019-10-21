/* Here's the receiver program. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>

/**ANCHOR o motivo de usar fila de memsagem foi a praticidade que ela nos da na adiminstração concorrencia
 * o unico problema com filas é genrenciar o tamanho maximo por mensagem  o tamanho maximo da dila de msg
 * as filas existem indempendente do processo de envio e recebimento de processo
 * 
 * o metodo msgget
 *       int msgget (key_t chave, int msgflg);
 * nessa chamda o sistema deve fornececer o uma chave que vai ser  o identificador da fila
 * uma permição de assesso que nesse sistema é passado 0666/ e o IPC_CREAT q tem valor 01000
 * 
 * o metodo msdsnd
 *      int  msgsnd ( int msqid, struct msgbuf *msgp, int msgsz,int msgflg )
 * 
 * Valor de retorno: 0 se a mensagem é colocada na fila e -1 em caso de erro.
 * 
 * o metodo msdsnd adiciona uma msg na fila para isso tem que passa a msqid que é a key da fila, a msgp que é a msg que sera
 *  adiconar e o msgsz que é o tamamnho maximo e a msgflg que controla o modo de envio
 * é usado a msgflg igual a zero apra bloquear a fila quando cheia.
 * 
 * o metodo msgrcv 
 *         int msgrcv ( int msqid, struct msgbuf *msgp, int msgsz,long msgtyp, int msgflg )
 * Valor de retorno: número de bytes da mensagem extraída da fila, ou -1 em caso de erro.
 * 
 * o metodo msgrcv recebe a msg da fila, para isso tem que adicionar o msqid que é o key da fila, passa o msgbuf
 * que é o tipo de dados que vai ser recebido, msgsz que é o tamanho maximo da msg a ser recebida, 
 * msgtyp que é o indicador de qual meg tem que receber e msgflg que controla o modo de execução da recepção da msnsagem
 * 
 * para msgtyp é usado 0 para sempre pegar a primeira msg da fila como usar a estrutura fifo ira recuperar a msg mais antiga da fila.
 * 
 */

typedef struct Musica
{
    char nome[256];
    char autor[256];
    char duracao[256];
    char genero[256];
} Musica;

int main()
{
    int running = 1;
    int msgid;
    struct Musica some_data;
    long int msg_to_receive = 0;

    /* First, we set up the message queue. */

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    /* Then the messages are retrieved from the queue, until an end message is encountered.
 Lastly, the message queue is deleted. */

    while (running)
    {
        if (msgrcv(msgid, (void *)&some_data, BUFSIZ,
                   msg_to_receive, 0) == -1)
        {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("Voce esta escutante: Musica: %s, Autor: %s, Duração: %s,  genero: %s  \n", some_data.nome, some_data.autor, some_data.duracao, some_data.genero);
        if (strncmp(some_data.nome, "end", 3) == 0 || strncmp(some_data.autor, "end", 3) == 0 || strncmp(some_data.duracao, "end", 3) == 0 || strncmp(some_data.genero, "end", 3) == 0)
        {
            running = 0;
        }
    }

    if (msgctl(msgid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
