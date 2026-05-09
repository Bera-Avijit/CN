#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int msgid;
    key_t key;

    key = 131;

    msgid = msgget(key, IPC_CREAT | 0666);

    if(msgid == -1)
    {
        printf("Message Queue Creation Failed\n");
    }
    else
    {
        printf("Message Queue Created Successfully\n");
        printf("Message Queue ID = %d\n", msgid);
    }

    return 0;
}
