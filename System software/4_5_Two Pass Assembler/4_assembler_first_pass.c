#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct
{
    char label[40], opcode[40], operand[40];
} pgm;

struct
{
    char opcode[40];
    int value;
} optab[1000];
int optab_len = 0;

struct
{
    char label[40];
    int value;
} symtab[1000];
int symtab_len = 0;

int searchOptab(char opcode[40])
{
    for (int i = 0; i < optab_len; i++)
    {
        if (strcmp(opcode, optab[i].opcode) == 0)
            return 1;
    }

    return 0;
}

int searchSymtab(char label[40])
{
    for (int i = 0; i < symtab_len; i++)
    {
        if (strcmp(label, symtab[i].label) == 0)
            return 1;
    }

    return 0;
}

void main()
{
    FILE *pgm_ptr, *optab_ptr, *intermediate_ptr, *symtab_ptr;
    int location_ctr = 0x0;
    int starting_address = 0x0;

    optab_ptr = fopen("input/optab.txt", "r");
    while (fscanf(optab_ptr, "%s%X", optab[optab_len].opcode, &optab[optab_len].value) != EOF)
        optab_len++;

    // Reading program
    pgm_ptr = fopen("input/source_code.txt", "r");
    intermediate_ptr = fopen("op/intermediate_code.txt", "w");

    printf("Reading Program\n");
    printf("Generating Symtab\n");
    printf("Generating Intermediate Code\n");
    symtab_ptr = fopen("op/symtab.txt", "w");

    while (fscanf(pgm_ptr, "%s%s%s", pgm.label, pgm.opcode, pgm.operand) != EOF)
    {
        int temp = location_ctr;

        if (strcmp(pgm.opcode, "START") == 0)
        {
            location_ctr = strtol(pgm.operand, NULL, 16);
            starting_address = strtol(pgm.operand, NULL, 16);
        }
        else if (searchOptab(pgm.opcode) || (strcmp(pgm.opcode, "WORD") == 0))
        {
            location_ctr += 3;
        }
        else if ((strcmp(pgm.opcode, "RESW") == 0))
        {
            location_ctr = location_ctr + 3 * strtol(pgm.operand, NULL, 10);
        }
        else if ((strcmp(pgm.opcode, "RESB") == 0))
        {
            location_ctr += strtol(pgm.operand, NULL, 10);
        }
        else if ((strcmp(pgm.opcode, "BYTE") == 0))
        {
            if (pgm.operand[0] == 'X')
            {
                location_ctr += (strlen(pgm.operand) - 3) / 2;
            }
            else if (pgm.operand[0] == 'C')
            {
                location_ctr += (strlen(pgm.operand) - 3);
            }
        }
        else if (strcmp(pgm.opcode, "END") == 0)
        {
        }
        else
        {
            printf("ERROR: INVALID OPCODE, %s", pgm.opcode);
        }

        // Intermediate file generation
        if (strcmp(pgm.opcode, "START") == 0)
        {
            fprintf(intermediate_ptr, "%-7X%-10s%-10s%-10s\n", location_ctr, pgm.label, pgm.opcode, pgm.operand);
        }
        else
        {
            fprintf(intermediate_ptr, "%-7X%-10s%-10s%-10s\n", temp, pgm.label, pgm.opcode, pgm.operand);
        }

        // Symtab generation
        if (!searchSymtab(pgm.label) && !(strcmp(pgm.label, "**") == 0))
        {
            strcpy(symtab[symtab_len].label, pgm.label);

            if (strcmp(pgm.opcode, "START") == 0)
                symtab[symtab_len].value = location_ctr;
            else
                symtab[symtab_len].value = temp;

            fprintf(symtab_ptr, "%-10s%10X\n", symtab[symtab_len].label, symtab[symtab_len].value);
            symtab_len++;
        }
        else
        {
            if (!(strcmp(pgm.label, "**") == 0))
                printf("ERROR: DUPLICATE LABEL, %s\n", pgm.label);
        }
    }

    printf("Computing Program Length\n");
    symtab_ptr = fopen("op/program_length.txt", "w");
    fprintf(symtab_ptr, "%X", location_ctr - starting_address);

    fclose(pgm_ptr);
    fclose(optab_ptr);
    fclose(intermediate_ptr);
    fclose(symtab_ptr);

    printf("Assembler: PASS 1 done...\n");
}
