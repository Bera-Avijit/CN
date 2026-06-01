// Server

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAX 20
#define PORT 5777

int main(){
    int sfd, cfd, i, j, n;
    char msg[100], rev[100];

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in saddr, caddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);

    bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr));
    listen(sfd, 1);

    cfd = accept(sfd, NULL, NULL);

    printf("Client Connected !!\n");

    while(1){
        n = read(cfd, msg, sizeof(msg));
        if(n<=0)
            break;
        msg[n] = '\0';

        for(i=n-1,j=0; i>=0; i--,j++){
            rev[j] = msg[i];
        }
        rev[j] = '\0';
        write(cfd, rev, strlen(rev));
    }
    close(sfd);
    close(cfd);

    return 0;
}


// Client

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAX 20
#define PORT 5777

int main(){
    int sockfd;
    char msg[100], rev[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    printf("Enter str : ");

    fgets(msg, MAX, stdin);

    write(sockfd, msg, strlen(msg));

    int n = read(sockfd, rev, sizeof(rev));
    rev[n] = '\0';

    printf("Reversed String: %s\n", rev);
    
    close(sockfd);

    return 0;
}
