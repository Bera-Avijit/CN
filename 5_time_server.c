// Server 

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

int main()
{
    int sfd, cfd;

    char smsg[100], cmsg[100];

    time_t t;

    struct sockaddr_in saddr;

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(4006);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));

    listen(sfd, 5);

    printf("Server Waiting...\n");

    cfd = accept(sfd, NULL, NULL);

    read(cfd, cmsg, sizeof(cmsg));

    printf("Client: %s\n", cmsg);

    t = time(NULL);

    strcpy(smsg, ctime(&t));

    write(cfd, smsg, sizeof(smsg));

    close(cfd);
    close(sfd);

    return 0;
}


// Client

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int cfd;

    char smsg[100], cmsg[100];

    struct sockaddr_in saddr;

    cfd = socket(AF_INET, SOCK_STREAM, 0);

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(4006);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(cfd,
           (struct sockaddr*)&saddr,
           sizeof(saddr));

    printf("Enter Message: ");

    fgets(cmsg, sizeof(cmsg), stdin);

    write(cfd, cmsg, sizeof(cmsg));

    read(cfd, smsg, sizeof(smsg));

    printf("Server Time: %s\n", smsg);

    close(cfd);

    return 0;
}
