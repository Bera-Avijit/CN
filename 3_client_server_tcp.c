// Server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int serv_sockfd, cli_sockfd;
    int serv_len, cli_len;

    struct sockaddr_in serv_address, cli_addr;

    char a[100], b[100];

    serv_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = 9002;
    serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    serv_len = sizeof(serv_address);

    bind(serv_sockfd, (struct sockaddr *)&serv_address, serv_len);

    listen(serv_sockfd, 5);

    while(1)
    {
        printf("Server is waiting...\n");

        cli_len = sizeof(cli_addr);

        cli_sockfd = accept(serv_sockfd,
                           (struct sockaddr *)&cli_addr,
                           &cli_len);

        read(cli_sockfd, a, sizeof(a));

        printf("Reading message from client...\n");
        puts(a);

        printf("Enter message for client: ");
        gets(b);

        write(cli_sockfd, b, sizeof(b));

        close(cli_sockfd);
    }

    return 0;
}


// Client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd, len, result;

    struct sockaddr_in address;

    char name[100], reply[100];

    address.sin_family = AF_INET;
    address.sin_port = 9002;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(address);

    while(1)
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        result = connect(sockfd,
                         (struct sockaddr *)&address,
                         len);

        if(result == -1)
        {
            perror("Connection Failed");
            exit(1);
        }

        printf("Enter message: ");
        gets(name);

        write(sockfd, name, sizeof(name));

        read(sockfd, reply, sizeof(reply));

        printf("Server Reply: ");
        puts(reply);

        close(sockfd);
    }

    return 0;
}
