// Arquivo mq-send.c: envia mensagens para uma fila de mensagens POSIX.
// Em Linux, compile usando: cc -o mq-send -lrt mq-send.c

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>

// operating system check
#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) && (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este codigo foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilacao e execucao em outros ambientes e responsabilidade do usuario.
#endif

#define QUEUE "/my_queue"

int main(int argc, char *argv[])
{
    mqd_t queue; // descritor da fila
    int msg;     // mensagem a enviar

    // abre a fila de mensagens, se existir
    if ((queue = mq_open(QUEUE, O_RDWR)) < 0)
    {
        perror("mq_open");
        exit(1);
    }

    for (;;)
    {
        msg = random() % 100; // valor entre 0 e 9926

        // envia a mensagem
        if (mq_send(queue, (void *)&msg, sizeof(msg), 0) < 0)
        {
            perror("mq_send");
            exit(1);
        }
        printf("Sent message with value %d\n", msg);
        sleep(1);
    }
}