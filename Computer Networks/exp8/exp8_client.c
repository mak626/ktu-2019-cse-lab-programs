#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	printf("DNS LOOKUP..\n");
	printf("Client Program..\n");
	char domain[45] = "";
	char recieve[60] = "";
	int sskt =  socket(AF_INET, SOCK_DGRAM, 0);
	
	struct sockaddr_in addr;
	int addrlen = sizeof(addr);
	
	addr.sin_family = AF_INET;
	addr.sin_port =  3002;
	addr.sin_addr.s_addr = INADDR_ANY;
	
	while(1)
	{
		printf("\nEnter a site address: ");
		scanf("%[^\n]%*c", domain);
		sendto(sskt, domain, sizeof(domain), 0, (struct sockaddr *) &addr, sizeof(addr));
		recvfrom(sskt, recieve, sizeof(recieve), 0, (struct sockaddr *) &addr, &addrlen);
		printf("IP: %s\n", recieve);
	}
}
