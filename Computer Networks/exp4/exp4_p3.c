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
	printf("Process 3");
	
	int fd;
	char *fileName1 = "f2.txt", data[500];
	
	fd = open(fileName1, O_RDONLY);
	read(fd, data, sizeof(data));
	close(fd);
		
	printf("%s", data);
}
