/*
	EXP4: IMPLEMENTATION OF IPC USING NAMED PIPE
	M ASWIN KISHORE
	41 S6 CS2
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main()
{
	printf("Process 1");
	
	int fd;
	char *fileName = "f1.txt" , data[500];
	
	mkfifo(fileName, 0666);
	
	printf("\nEnter data:");
	scanf("%[^\n]%*c", data);
	
	fd = open(fileName, O_WRONLY);
	write(fd, data, sizeof(data));
	close(fd);
}
