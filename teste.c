/* arquivo test_msgget.c */
/**  exemplo de utilizacao de msgget()*/
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#define KEY 123
int main()
{
    int msqid;
    /* ID da fila de mensagens */
    char *path = "nome_de_arquivo_existente";
    /** criacao de uma fila de mensagens para leitura se* ela ainda nao existe*/
    if ((msqid = msgget(ftok(path, (key_t)KEY), IPC_CREAT | IPC_EXCL | 0600)) == -1)
    {
        perror("Erro de msgget");
        exit(1);
    }
    printf("identificador da fila: %d\n", msqid);
    printf("esta fila esta associada a chave unica : %#x\n", ftok(path, (key_t)KEY));
    exit(0);
}