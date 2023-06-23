#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	printf("FTP: Client Program 1..\n");
	char buffer[500] = "";
	char fileName[40];
	
	do{
		int sskt = socket(AF_INET, SOCK_STREAM, 0);
	
		struct sockaddr_in addr1;
		
		addr1.sin_family = AF_INET;
		addr1.sin_port =  3000;
		addr1.sin_addr.s_addr = INADDR_ANY;
		
		int errno = connect(sskt,(struct sockaddr *) &addr1, sizeof(addr1));
	
	
		if(errno == -1)
		{
			perror("ERROR");
			return;
		}
		
		printf("\nEnter filename:");
		scanf("%s", fileName);
		send(sskt, fileName, sizeof(fileName), 0);
		recv(sskt, buffer, sizeof(buffer), 0);
		printf("Server Response:\n%s", buffer);
		
		if(strcmp(buffer,"File Doesn't Exist") != 0)
		{
			char writeFilePath[100] = "client1/";
			strcat(writeFilePath,fileName);
			printf("\nWriting responce to file: %s", writeFilePath);
			FILE *f = fopen(writeFilePath,"w");
			fprintf(f,"%s",buffer);
			fclose(f);
		}
		
		printf("\n");
		close(sskt);
	}while(strcmp(buffer,"stop"));
}
