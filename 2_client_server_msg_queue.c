// Server

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>

struct msgbuf
{
    long mtype;
    char mtext[100];
};

int main()
{
    int qid;
    struct msgbuf send, recv;

    qid = msgget((key_t)125, IPC_CREAT | 0666);

    if(qid < 0)
    {
        perror("msgget failed");
        exit(1);
    }

    msgrcv(qid, &recv, 100, 1, 0);

    printf("Message from Client: %s\n", recv.mtext);

    printf("Enter reply for Client: ");
    scanf("%[^\n]s", send.mtext);

    send.mtype = 2;

    msgsnd(qid, &send, strlen(send.mtext)+1, 0);

    return 0;
}




// Client 

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>

struct msgbuf
{
    long mtype;
    char mtext[100];
};

int main()
{
    int qid;
    struct msgbuf send, recv;

    qid = msgget((key_t)125, IPC_CREAT | 0666);

    if(qid < 0)
    {
        perror("msgget failed");
        exit(1);
    }

    printf("Enter message for Server: ");
    scanf("%[^\n]s", send.mtext);

    send.mtype = 1;

    msgsnd(qid, &send, strlen(send.mtext)+1, 0);

    msgrcv(qid, &recv, 100, 2, 0);

    printf("Reply from Server: %s\n", recv.mtext);

    return 0;
}
