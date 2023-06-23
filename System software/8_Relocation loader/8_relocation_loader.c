#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Say we have a OrginalNumber = 0001 0100 0 (length = 9)
    I want the bit at 4th position that is bit 1

    Now lets shift the a new number 1 (BIN: 01) to left by 5 times [length - position = 9 - 4 = 5]
    Now we get 0100000

    Now lets AND both numbers
    000101000
    000100000
    --------
    000100000 RESULT

    Now to actually check whether the bit at pos 4 was 1 or 0
    Simply right shift the RESULT by 5 times
    0001 which is internally 1.
*/
int get_bit(int n, int pos)
{
    int offset = 12 - pos; // 12 is maximum no. of bits in FFF

    int mask = 1 << offset;
    int and_result = n & mask;
    int bit = and_result >> offset;

    return bit;
}

void main()
{
    FILE *record_ptr;
    int program_len = 0x0, starting_addr = 0x0, relocationOffset, headerRecordLengthMismatch = 1;
    char temp[300];

    printf("Enter relocation address in HEX: ");
    scanf("%x", &relocationOffset);

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

            starting_addr = relocationOffset;

            printf("\nProgram Name: %s\n", instructions[1]);
            printf("Program Starting Address: %X\n", starting_addr);
            printf("Program Length: %s\n", instructions[3]);

            printf("\n%6s |  %6s\n", "ADDRESS", "OBJCODE");
            printf("------------------\n");
        }
        else if (strcmp("T", instructions[0]) == 0)
        {

            int text_starting_addr = strtol(instructions[1], NULL, 16) + relocationOffset;
            int bitmask = strtol(instructions[3], NULL, 16);

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

            for (int j = 4, i = 1; j < text_len; j++, i++)
            {
                if (get_bit(bitmask, i)) // REALOCATE
                {
                    int obj_code = strtol(instructions[j], NULL, 16);
                    printf("%06X  |  %06X\n", text_starting_addr, obj_code + relocationOffset);
                }
                else
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
    printf("\nRelocation Loader done...\n");
}