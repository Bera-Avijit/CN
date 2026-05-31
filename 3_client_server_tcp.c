// Server

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    int serv_sock, cli_sock;
    int serv_len, cli_len;
    char a[100], b[100];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr, cli_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9001);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    serv_len = sizeof(serv_addr);
    
    bind(serv_sock, (struct sockaddr *)&serv_addr, serv_len);

    listen(serv_sock, 5);
    printf("Server Waiting !!\n");
    
    cli_len = sizeof(cli_addr);
    cli_sock = accept(serv_sock, (struct sockaddr *)&cli_addr, &cli_len);
    printf("Client Connected !!\n");
    while(1){
        read(cli_sock, a, sizeof(a));
        printf("Client : %s\n", a);
        printf("Server : ");
        gets(b);
        write(cli_sock, b, sizeof(b));
    }
    close(serv_sock);
    close(cli_sock);

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

int main(){
    int sock, len, result;
    char a[100], b[100];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9001);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(addr);

    result = connect(sock, (struct sockaddr *)&addr, len);
    if(result == -1)
    {
        perror("Unable to connect");
        exit(1);
    }

    printf("Server Connected !!\n");

    while(1){
        printf("Client : ");
        gets(a);
        write(sock, a, sizeof(a));
        read(sock, b, sizeof(b));
        printf("Server : %s\n", b);
    }
    close(sock);

    return 0;
}
