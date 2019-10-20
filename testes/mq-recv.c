// Arquivo mq-recv.c: recebe mensagens de uma fila de mensagens POSIX.
// Em Linux, compile usando: cc -o mq-recv -lrt mq-recv.c

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>

// operating system check
#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) && (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este codigo foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilacao e execucao em outros ambientes e responsabilidade do usuario.
#endif

#define QUEUE "/my_queue"

int main(int argc, char *argv[])
{
    mqd_t queue;         // descritor da fila de mensagens
    struct mq_attr attr; // atributos da fila de mensagens
    int msg;             // as mensagens são números inteiros

    // define os atributos da fila de mensagens
    attr.mq_maxmsg = 10;           // capacidade para 10 mensagens
    attr.mq_msgsize = sizeof(msg); // tamanho de cada mensagem
    attr.mq_flags = 0;

    // abre ou cria a fila com permissoes 0666
    if ((queue = mq_open (QUEUE, O_RDWR | O_CREAT, 0666, &attr)) < 0)
    {
        perror("mq_open");
        exit(1);
    }

    // recebe cada mensagem e imprime seu conteudo
    for (;;)
    {
        if ((mq_receive (queue, (void *)&msg, sizeof(msg), 0)) < 0)
        {
            perror("mq_receive:");
            exit(1);
        }
        printf("Received msg value %d\n", msg);
    }
}
