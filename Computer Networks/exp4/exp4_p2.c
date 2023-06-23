/*
    EXP4: IMPLEMENTATION OF IPC USING NAMED PIPE
    M ASWIN KISHORE
    41 S6 CS2
*/

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
    printf("Process 2");

    int chars = 0, words = 0, sentences = 0, vowels = 0, fd;

    char *fileName = "f1.txt", *fileName1 = "f2.txt", data[500];

    mkfifo(fileName1, 0666);

    fd = open(fileName, O_RDONLY);
    read(fd, data, sizeof(data));
    close(fd);

    printf("\nRecieved Data : %s", data);

    char vowelsArr[7] = "aeiou";
    for (int i = 0; i < strlen(data); i++)
    {
        if (isalnum(data[i]))
            chars++;
        if (data[i] == '\t' || data[i] == '\n' || data[i] == ' ' || data[i] == '.')
            words++;
        if (data[i] == '.')
            sentences++;
        for (int j = 0; j < 5; j++)
            if (vowelsArr[j] == tolower(data[i]))
                vowels++;
    }

    fd = open(fileName1, O_WRONLY);
    printf("\nCalculated Count");
    sprintf(data, "\nChars: %d Words:%d Sentences:%d Vowels:%d", chars, words, sentences, vowels);

    write(fd, data, sizeof(data));
    close(fd);
}
