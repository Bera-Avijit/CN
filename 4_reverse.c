// Server

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX 20
#define PORT 5777

int main()
{
    int sfd, cfd, i, j, n;

    char msg[MAX], rev[MAX];

    struct sockaddr_in saddr, caddr;

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&saddr, sizeof(saddr));

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);

    bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));

    listen(sfd, 1);

    cfd = accept(sfd, NULL, NULL);

    printf("Connected to Client\n");

    while(1)
    {
        n = read(cfd, msg, MAX);

        if(n <= 0)
            break;

        msg[n] = '\0';

        for(i = n - 1, j = 0; i >= 0; i--, j++)
        {
            rev[j] = msg[i];
        }

        rev[j] = '\0';

        write(cfd, rev, strlen(rev));
    }

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

#define MAX 20
#define PORT 5777

int main()
{
    int cfd;

    char msg[MAX], rev[MAX];

    struct sockaddr_in saddr;

    cfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&saddr, sizeof(saddr));

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);

    connect(cfd, (struct sockaddr*)&saddr, sizeof(saddr));

    printf("Enter String: ");

    fgets(msg, MAX, stdin);

    write(cfd, msg, strlen(msg));

    read(cfd, rev, MAX);

    printf("Reversed String: %s\n", rev);

    close(cfd);

    return 0;
}
