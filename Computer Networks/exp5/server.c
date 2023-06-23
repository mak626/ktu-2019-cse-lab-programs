#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	printf("Server Program..\n");
	char buffer[500] = "";
	int sskt = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr1, addr2;
	int addr2_size = sizeof(addr2);
	
	addr1.sin_family = AF_INET;
	addr1.sin_port =  3008;
	addr1.sin_addr.s_addr = INADDR_ANY;
	
	bind(sskt,(struct sockaddr *) &addr1, sizeof(addr1));
	listen(sskt, 5);
	
	int cskt = accept(sskt, (struct sockaddr *) &addr2, (&addr2_size));
	printf("\n*** Connection Established ***\n");
	
	do{
		recv(cskt, buffer, sizeof(buffer) , 0);
		printf("\nMessage from client: %s", buffer);
		printf("\nEnter message for client:");
		scanf("%[^\n]%*c", buffer);
		send(cskt, buffer, sizeof(buffer) , 0);
	}while(strcmp(buffer,"stop"));
	
	close(sskt);
	close(cskt);
}
