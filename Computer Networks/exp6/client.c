// CLIENT
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

void main()
{
    printf("Client\n");
    struct sockaddr_in server, client;
    int skt, addrlen;
    char buffer[50];

    skt = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = 3008;
    server.sin_addr.s_addr = INADDR_ANY;

    addrlen = sizeof(server);

    do
    {
        printf("Sending message to server: ");
        scanf("%s", buffer);

        sendto(skt, buffer, sizeof(buffer), 0, (struct sockaddr *)&server, addrlen);
        recvfrom(skt, buffer, sizeof(buffer), 0, NULL, NULL);

        printf("Received from server: %s\n", buffer);
    } while (strcmp(buffer, "stop") != 0);
}
