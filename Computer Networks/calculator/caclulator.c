/*
    M ASWIN KISHORE
    41 S6 CS2
    EXP2 : FORK IMPLEMENTATION
*/

#include <limits.h>
#include <stdio.h>

void main()
{
    // -----------------------------------------------------------------------------------
    // Client
    int num1, num2;
    char op, buffer[1000] = "";

    printf("Enter binary operator: "); // +,-,/,*
    scanf("%s", &op);
    printf("Enter two nums: ");
    scanf("%d%d", &num1, &num2);

    sprintf(buffer, "%c %d %d", op, num1, num2);
    // Send buffer to server
    printf("This string is to be send to server : \"%s\"\n", buffer);

    // -----------------------------------------------------------------------------------
    // Server
    // recv buffer from client
    int s_num1, s_num2, result;
    char s_op, s_buffer[1000] = "";
    sscanf(buffer, "%c %d %d", &s_op, &s_num1, &s_num2); // similar to scanf but from a string instead of terminal.

    printf("operator: %c\nNum1: %d\nNum2: %d", s_op, s_num1, s_num2);

    int invalid_op = 0;

    switch (s_op)
    {
    case '+':
        result = s_num1 + s_num2;
        break;

    case '-':
        result = s_num1 - s_num2;
        break;

    case '/':
        result = s_num1 / s_num2;
        break;

    case '*':
        result = s_num1 * s_num2;
        break;

    default:
        invalid_op = 1; // Indicates invalid
    }

    if (invalid_op != 1)
    {
        sprintf(s_buffer, "Result: %d", result);
    }
    else
    {
        sprintf(s_buffer, "Invalid Operator: %c", op);
    }

    printf("\n\ns_buffer: %s\n", s_buffer);
    // Send s_buffer to client and print it.
}

/*
OUTPUT

Enter binary operator: +
Enter two nums: 50 40
This string is to be send to server : "+ 50 40"
operator: +
Num1: 50
Num2: 40

s_buffer: Result: 90
*/
