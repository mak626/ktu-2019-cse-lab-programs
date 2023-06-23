/*
MOV DEST, SOURCE

A=B+C

MOV ax,B
ADD ax,C
MOV A,ax
*/

#include <stdio.h>
#include <string.h>

void main()
{
    FILE *fp = fopen("input.txt", "r");

    char in[200] = "";
    while (fscanf(fp, "%[^\n]%*c", in) != EOF)
    {
        char r, a, b, op;

        if (in[0] == 'i' && in[1] == 'f')
        {
            char a[3], b[3], op[3], res[3];
            // if X > Y , goto Z
            sscanf(in, "%*s%s%s%s%*s%*s%s", a, op, b, res);

            printf("MOV AX, %s\n", a);
            printf("CMP AX, %s\n", b);

            if (strcmp(op, "<") == 0)
                printf("JL %s\n", res);
            else if (strcmp(op, "<=") == 0)
                printf("JLE %s\n", res);
            else if (strcmp(op, ">") == 0)
                printf("JG %s\n", res);
            else if (strcmp(op, ">=") == 0)
                printf("JGE %s\n", res);
            else if (strcmp(op, "=") == 0)
                printf("JE %s\n", res);
            else if (strcmp(op, "!=") == 0)
                printf("JNE %s\n", res);
        }
        else
        {
            //            %*c will remove = , note that right side has only 4 vars not 5
            sscanf(in, "%c%*c%c%c%c", &r, &a, &op, &b);

            printf("MOV AX,%c\n", a);

            switch (op)
            {
            case '+':
                printf("ADD AX,%c\n", b);
                break;
            case '-':
                printf("SUB AX,%c\n", b);
                break;
            case '/':
                printf("DIV AX,%c\n", b);
                break;
            case '*':
                printf("MUL AX,%c\n", b);
                break;
            default:
                break;
            }

            printf("MOV %c,AX\n", r);
        }
    }
}