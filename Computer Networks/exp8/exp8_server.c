#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
    printf("DNS LOOKUP..\n");
    printf("Server Program..\n");

    char recievedDomain[45] = "", ip[40], domain[40], defaultMessage[] = "NO IP FOUND";
    FILE *f;
    int sskt = socket(AF_INET, SOCK_DGRAM, 0), found;

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = 3002;
    addr.sin_addr.s_addr = INADDR_ANY;

    int addrlen = sizeof(addr);

    bind(sskt, (struct sockaddr *)&addr, sizeof(addr));

    while (1)
    {
        recvfrom(sskt, recievedDomain, sizeof(recievedDomain), 0, (struct sockaddr *)&addr, &addrlen);
        printf("Client DNS Request: %s\n", recievedDomain);

        f = fopen("dns.txt", "r");
        found = 0;

        while (fscanf(f, "%s%s", domain, ip) != EOF)
        {
            if (strcasecmp(domain, recievedDomain) == 0)
            {
                found = 1;
                sendto(sskt, ip, sizeof(ip), 0, (struct sockaddr *)&addr, sizeof(addr));
                break;
            }
        }

        if (found == 0)
            sendto(sskt, defaultMessage, sizeof(defaultMessage), 0, (struct sockaddr *)&addr, sizeof(addr));

        fclose(f);
    }
}
