#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct
{
    char to[45], from[45], sub[45], message[200];
} email;

void main()
{
    printf("SMTP..\n");
    printf("Client Program..\n");
    char buffer[50] = "";
    int sskt = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr1;

    addr1.sin_family = AF_INET;
    addr1.sin_port = 3001;
    addr1.sin_addr.s_addr = INADDR_ANY;

    int errno = connect(sskt, (struct sockaddr *)&addr1, sizeof(addr1));
    if (errno == -1)
    {
        printf("\nXXX Connection Failed XXX\n");
        return;
    }
    else
        printf("\n*** Connection Established ***\n");

    while (1)
    {
        printf("\nEnter Reciepient Email:");
        scanf("%s", email.to);

        printf("Enter Sender Email:");
        scanf("%s", email.from);

        printf("Enter Subject:");
        scanf("%s", email.sub);

        printf("Enter Message:");
        scanf("%s", email.message);

        send(sskt, email.to, sizeof(email.to), 0);
        send(sskt, email.from, sizeof(email.from), 0);
        send(sskt, email.sub, sizeof(email.sub), 0);
        send(sskt, email.message, sizeof(email.message), 0);

        recv(sskt, buffer, sizeof(buffer), 0);
        printf("\n\nReciepient Domain Name: %s\n", buffer);

        recv(sskt, buffer, sizeof(buffer), 0);
        printf("Sender Domain Name: %s\n", buffer);
    };

    close(sskt);
}

/*
john@gmail.com
jane@gmail.com
TestEmail
Hello

*/
