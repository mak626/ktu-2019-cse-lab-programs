// Server
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void main()
{
    printf("Server Side\n");
    char buffer[50];
    int skt;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 3008;
    addr.sin_addr.s_addr = INADDR_ANY;

    int addrlen = sizeof(struct sockaddr_in);

    skt = socket(AF_INET, SOCK_DGRAM, 0);
    bind(skt, (struct sockaddr *)&addr, sizeof(addr));

    while (1)
    {
        recvfrom(skt, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &addrlen);
        printf("Received message from client : %s\n", buffer);

        pid_t pid = fork();
        if (pid == 0)
        {
            time_t rawtime;
            struct tm *timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            sprintf(buffer, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
            sendto(skt, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, addrlen);
        }
    }

    close(skt);
}