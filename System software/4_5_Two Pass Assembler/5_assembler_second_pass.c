#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct
{
    int address;
    char label[50];
    char opcode[50];
    char operand[50];
} inter_file;

int program_len = 0;

struct
{
    char opcode[50];
    int value;
} optab[1000];

int optab_length = 0;

struct
{
    char label[50];
    int value;
} symtab[1000];

int sym_length = 0;

int searchOptab(char *opcode)
{
    for (int i = 0; i < optab_length; i++)
    {
        if (strcmp(optab[i].opcode, opcode) == 0)
            return i;
    }
    return -1;
}

int searchSymtab(char *label)
{
    for (int i = 0; i < sym_length; i++)
    {
        if (strcmp(symtab[i].label, label) == 0)
            return i;
    }

    return -1;
}

void writeTextRecord(FILE *temp_ptr, FILE *record_ptr, int *obj_len, int *starting_addr)
{
    char str[100];

    fclose(temp_ptr);
    fprintf(record_ptr, "\nT^%06X^%02X", *starting_addr, *obj_len);

    temp_ptr = fopen("op2/temp.txt", "r");
    fscanf(temp_ptr, "%s", str);
    fprintf(record_ptr, "%s", str);
    fclose(temp_ptr);
}

void checkTextRecordLimit(FILE *temp_ptr, FILE *record_ptr, int *obj_len, int *starting_addr, int offset, int new_starting_addr, int *pgm_obj_staring_addr)
{
    if (*starting_addr == -1)
        *starting_addr = new_starting_addr;

    if (*pgm_obj_staring_addr == -1)
        *pgm_obj_staring_addr = new_starting_addr;

    if ((*obj_len + offset) * 2 > 60)
    {
        writeTextRecord(temp_ptr, record_ptr, obj_len, starting_addr);

        // Re-Initialize
        *obj_len = 0;
        temp_ptr = fopen("op2/temp.txt", "w");
        *starting_addr = new_starting_addr;
    }
}

void main()
{
    FILE *inter_ptr, *record_ptr, *pgmlen_ptr, *optab_ptr, *symtab_ptr, *temp_ptr;
    inter_ptr = fopen("op/intermediate_code.txt", "r");
    pgmlen_ptr = fopen("op/program_length.txt", "r");
    symtab_ptr = fopen("op/symtab.txt", "r");
    optab_ptr = fopen("input/optab.txt", "r");

    record_ptr = fopen("op2/record.txt", "w");
    temp_ptr = fopen("op2/temp.txt", "w");

    printf("Reading Symtab\n");
    while (fscanf(symtab_ptr, "%s%X", symtab[sym_length].label, &symtab[sym_length].value) != EOF)
        sym_length++;

    printf("Reading Optab\n");
    while (fscanf(optab_ptr, "%s%X", optab[optab_length].opcode, &optab[optab_length].value) != EOF)
        optab_length++;

    printf("Reading program length\n");
    fscanf(pgmlen_ptr, "%X", &program_len);

    int obj_len = 0, starting_addr = -1, pgm_obj_staring_addr = -1;

    printf("Reading intermediate file\n");
    printf("Generating record file\n");
    while (fscanf(inter_ptr, "%X%s%s%s", &inter_file.address, inter_file.label, inter_file.opcode, inter_file.operand) != EOF)
    {
        if (strcmp(inter_file.opcode, "START") == 0)
        {
            fprintf(record_ptr, "H^%6.6s^%06s^%06X", inter_file.label, inter_file.operand, program_len);
        }

        else if (searchOptab(inter_file.opcode) != -1)
        {
            checkTextRecordLimit(temp_ptr, record_ptr, &obj_len, &starting_addr, 3, inter_file.address, &pgm_obj_staring_addr);

            int op_pos = searchOptab(inter_file.opcode);
            int sym_pos = searchSymtab(inter_file.operand);

            if (sym_pos != -1)
            {
                fprintf(temp_ptr, "^%02X%X", optab[op_pos].value, symtab[sym_pos].value);
            }

            // Index Addressing
            else if (strstr(inter_file.operand, ",X"))
            {
                char label[40] = "";
                strncpy(label, inter_file.operand, strlen(inter_file.operand) - 2);

                int sym_pos = searchSymtab(label);

                if (sym_pos != -1)
                {
                    int value = symtab[sym_pos].value + 0x8000;
                    fprintf(temp_ptr, "^%02X%X", optab[op_pos].value, value);
                }
                else
                {
                    printf("ERROR: SYMBOL NOT FOUND IN SYMTAB: %s\n", inter_file.operand);
                    fprintf(temp_ptr, "^%02X%04X", optab[op_pos].value, 0x0);
                }
            }

            else
            {
                if (strcmp(inter_file.operand, "**") != 0)
                    printf("ERROR: SYMBOL NOT FOUND IN SYMTAB: %s\n", inter_file.operand);
                fprintf(temp_ptr, "^%02X%04X", optab[op_pos].value, 0x0);
            }

            obj_len += 3;
        }

        else if (strcmp(inter_file.opcode, "BYTE") == 0)
        {
            float temp_len = 0;
            for (int i = 0; i < strlen(inter_file.operand); i++)
            {
                if (inter_file.operand[i] == 'C' || inter_file.operand[i] == 'X' || inter_file.operand[i] == '\'')
                    continue;

                // THIS IS A BUG to be fixed in previous programs
                if (pgm.operand[0] == 'C')
                    temp_len += 2;
                else if (pgm.operand[0] == 'X')
                    temp_len += 1;
            }

            checkTextRecordLimit(temp_ptr, record_ptr, &obj_len, &starting_addr, temp_len / 2, inter_file.address, &pgm_obj_staring_addr);

            fprintf(temp_ptr, "%s", "^");
            for (int i = 0; i < strlen(inter_file.operand); i++)
            {
                if (inter_file.operand[i] == 'C' || inter_file.operand[i] == 'X' || inter_file.operand[i] == '\'')
                    continue;

                if (inter_file.operand[0] == 'X')
                    fprintf(temp_ptr, "%C", inter_file.operand[i]);
                else if (inter_file.operand[0] == 'C')
                    fprintf(temp_ptr, "%X", inter_file.operand[i]);
            }

            obj_len += temp_len / 2;
        }

        else if (strcmp(inter_file.opcode, "WORD") == 0)
        {
            checkTextRecordLimit(temp_ptr, record_ptr, &obj_len, &starting_addr, 3, inter_file.address, &pgm_obj_staring_addr);
            fprintf(temp_ptr, "^%06X", strtol(inter_file.operand, NULL, 10));
            obj_len += 3;
        }
    }

    if (obj_len != 0)
        writeTextRecord(temp_ptr, record_ptr, &obj_len, &starting_addr);

    fprintf(record_ptr, "\nE^%06X", pgm_obj_staring_addr);

    fclose(inter_ptr);
    fclose(record_ptr);
    fclose(pgmlen_ptr);
    fclose(optab_ptr);
    fclose(symtab_ptr);
    fclose(temp_ptr);

    printf("Removing temp file\n");
    remove("op2/temp.txt");

    printf("Assembler: PASS 2 done...\n");
}
