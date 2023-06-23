#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
    printf("Client Program..\n");
    char buffer[500] = "";
    int sskt = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr1;

    addr1.sin_family = AF_INET;
    addr1.sin_port = 3008;
    addr1.sin_addr.s_addr = INADDR_ANY;

    int errno = connect(sskt, (struct sockaddr *)&addr1, sizeof(addr1));
    if (errno == -1)
    {
        printf("\nXXX Connection Failed XXX\n");
        return;
    }
    else
        printf("\n*** Connection Established ***\n");

    do
    {
        printf("\nEnter message for server:");
        scanf("%[^\n]%*c", buffer);
        send(sskt, buffer, sizeof(buffer), 0);
        recv(sskt, buffer, sizeof(buffer), 0);
        printf("\nMessage from server: %s", buffer);
    } while (strcmp(buffer, "stop"));

    close(sskt);
}
