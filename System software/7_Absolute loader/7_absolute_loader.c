#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    FILE *record_ptr;
    int program_len = 0x0, starting_addr = 0x0, headerRecordLengthMismatch = 1;
    char temp[300];

    printf("Reading record\n");
    record_ptr = fopen("record.txt", "r");

    while (fscanf(record_ptr, "%[^\n]%*c", temp) != EOF)
    {
        // Split the string to an array of instructions seperated by ^
        char instructions[40][300];
        char *token = strtok(temp, "^");
        int text_len = 0;
        while (token != NULL)
        {
            strcpy(instructions[text_len], token);
            token = strtok(NULL, "^");
            text_len++;
        }

        if (strcmp("H", instructions[0]) == 0)
        {
            starting_addr = strtol(instructions[2], NULL, 16);
            program_len = strtol(instructions[3], NULL, 16);

            printf("\nProgram Name: %s\n", instructions[1]);
            printf("Program Starting Address: %s\n", instructions[2]);
            printf("Program Length: %s\n", instructions[3]);

            printf("\n%6s |  %6s\n", "ADDRESS", "OBJCODE");
            printf("------------------\n");
        }
        else if (strcmp("T", instructions[0]) == 0)
        {

            int text_starting_addr = strtol(instructions[1], NULL, 16);

            // If the first text record's starting address is not the same as header record starting address then
            // print xxxxxx untill we reach current text record address
            if (headerRecordLengthMismatch == 1)
            {
                headerRecordLengthMismatch = 0;
                if (starting_addr != text_starting_addr)
                {
                    for (int j = starting_addr; j < text_starting_addr; j += 3)
                        printf("%06X  |  %6s\n", j, "XXXXXX");
                }
            }

            for (int j = 3; j < text_len; j++)
            {
                printf("%06X  |  %6s\n", text_starting_addr, instructions[j]);
                text_starting_addr += strlen(instructions[j]) / 2;
            }
        }
        else if (strcmp("E", instructions[0]) == 0)
            break;
        else
            printf("ERROR: UNKNOWN RECORD");
    }

    fclose(record_ptr);
    printf("\nAbsolute Loader done...\n");
}