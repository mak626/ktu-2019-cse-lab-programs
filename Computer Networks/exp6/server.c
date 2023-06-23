// SERVER
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

void main()
{
    printf("Server\n");

    struct sockaddr_in server, client;
    int skt, addrlen;
    char buffer[50];

    skt = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = 3008;
    server.sin_addr.s_addr = INADDR_ANY;

    bind(skt, (struct sockaddr *)&server, sizeof(server));

    addrlen = sizeof(client);

    do
    {
        printf("Receiving message from client : ");
        recvfrom(skt, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &addrlen);
        printf("%s", buffer);

        printf("\nEnter the message:");
        scanf("%s", buffer);

        sendto(skt, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, addrlen);
    } while (strcmp(buffer, "stop") != 0);
}
