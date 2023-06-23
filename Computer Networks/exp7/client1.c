// Client 1
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
    printf("Client Side: 1\n");
    char buffer[50];

    int skt = socket(AF_INET, SOCK_DGRAM, 0);
    int addrlen = sizeof(struct sockaddr_in);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 3008;

    while (1)
    {
        printf("\nMessage: ");
        scanf("%s", buffer);
        sendto(skt, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, addrlen);
        recvfrom(skt, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &addrlen);
        printf("Received from server : %s\n", buffer);
    }

    close(skt);
}
