/*
    M ASWIN KISHORE
    41 S6 CS2
    EXP3 : Inter-process Communication using Pipes
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define R 0
#define W 1
#define MAX_LINE_WIDTH 1000

void main()
{
    int pipe1[2], pipe2[2], ret1, ret2;

    char fileName[40], buffer[MAX_LINE_WIDTH];

    ret1 = pipe(pipe1);
    ret2 = pipe(pipe2);

    if (ret1 == -1 || ret2 == -1)
    {
        printf("Piping Failed!");
        return;
    }

    pid_t pid = fork();

    if (pid > 0)
    {
        printf("\nIn Parent");
        printf("\nEnter filename: ");
        scanf("%s", fileName);

        close(pipe1[R]);
        write(pipe1[W], fileName, sizeof(fileName));

        sleep(5);

        printf("\nIn Parent");
        close(pipe2[W]);

        printf("\nRecieving contents of file from child");
        read(pipe2[R], buffer, sizeof(buffer));

        printf("\n\nContents:\n");
        printf("%s", buffer);
        printf("\n");
    }

    else if (pid == 0)
    {
        sleep(5);
        printf("\nIn Child");

        close(pipe1[W]);
        read(pipe1[R], fileName, sizeof(fileName));
        printf("\nRecieved File Name: %s", fileName);

        FILE *ptr = fopen(fileName, "r");
        printf("\nReading contents of file\n");
        fscanf(ptr, "%[^EOF]%*c", buffer);
        printf("%s", buffer);
        fclose(ptr);
        close(pipe2[R]);
        write(pipe2[W], buffer, sizeof(buffer));
    }

    else
    {
        printf("Fork Failed!");
    }
}
