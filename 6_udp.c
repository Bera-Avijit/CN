// Server

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sfd, len;

    char cmsg[200], smsg[200];

    struct sockaddr_in saddr, caddr;

    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8002);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));

    printf("UDP Server Waiting...\n");

    len = sizeof(caddr);

    while(1)
    {
        recvfrom(sfd,
                 cmsg,
                 sizeof(cmsg),
                 0,
                 (struct sockaddr*)&caddr,
                 &len);

        printf("Client: %s\n", cmsg);

        printf("Server: ");

        fgets(smsg, sizeof(smsg), stdin);

        sendto(sfd,
               smsg,
               strlen(smsg)+1,
               0,
               (struct sockaddr*)&caddr,
               len);
    }

    close(sfd);

    return 0;
}


// Client

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int cfd, len;

    char cmsg[200], smsg[200];

    struct sockaddr_in saddr;

    cfd = socket(AF_INET, SOCK_DGRAM, 0);

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8002);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(saddr);

    while(1)
    {
        printf("Client: ");

        fgets(cmsg, sizeof(cmsg), stdin);

        sendto(cfd,
               cmsg,
               strlen(cmsg)+1,
               0,
               (struct sockaddr*)&saddr,
               len);

        recvfrom(cfd,
                 smsg,
                 sizeof(smsg),
                 0,
                 NULL,
                 NULL);

        printf("Server: %s\n", smsg);
    }

    close(cfd);

    return 0;
}
