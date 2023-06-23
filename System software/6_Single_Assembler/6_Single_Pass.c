#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct
{
    int address;
    char label[40], opcode[40], operand[40], objcode[40];
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

struct LocationPtr
{
    int location;
    struct LocationPtr *next;
};

struct ForwardRef
{
    char label[40];
    struct LocationPtr *head;
} forward_ref[1000];
int forward_ref_len = 0;

// Serach functions

int searchOptab(char opcode[40])
{
    for (int i = 0; i < optab_len; i++)
    {
        if (strcmp(opcode, optab[i].opcode) == 0)
            return i;
    }

    return -1;
}

int searchSymtab(char label[40])
{
    for (int i = 0; i < symtab_len; i++)
    {
        if (strcmp(label, symtab[i].label) == 0)
            return i;
    }

    return -1;
}

// Record Writing functions

void writeTextRecord(FILE *temp_ptr, FILE *record_ptr, int *text_len, int *text_starting_addr, int new_starting_addr)
{
    if (*text_len != 0)
    {
        char str[100];

        fclose(temp_ptr);
        fprintf(record_ptr, "\nT^%06X^%02X", *text_starting_addr, *text_len);

        temp_ptr = fopen("op/temp.txt", "r");
        fscanf(temp_ptr, "%s", str);
        fprintf(record_ptr, "%s", str);
    }

    fclose(temp_ptr);
    // Initialization code moved here
    *text_len = 0;
    temp_ptr = fopen("op/temp.txt", "w");
    *text_starting_addr = new_starting_addr;
}

void checkTextRecordLimit(FILE *temp_ptr, FILE *record_ptr, int *text_len, int *text_starting_addr, int offset, int new_starting_addr, int *obj_staring_addr)
{
    if (*text_starting_addr == -1)
        *text_starting_addr = new_starting_addr;

    if (*obj_staring_addr == -1)
        *obj_staring_addr = new_starting_addr;

    if ((*text_len + offset) * 2 > 60)
    {
        writeTextRecord(temp_ptr, record_ptr, text_len, text_starting_addr, new_starting_addr);
        // MOVED initialization to writeTextRecord()
    }
}

// Forward Reference functions

int addToForwardRef(char label[40], int location)
{
    int i;

    // Create a location node to store the current location value to linkedList
    struct LocationPtr *newLocationPtr = (struct LocationPtr *)malloc(sizeof(struct LocationPtr));
    newLocationPtr->location = location + 1; // We need location field only - XXYYYY (XX-OPCODE) (YYYY-LOCATION)
    newLocationPtr->next = NULL;

    // Check if it a forward_ref already exists in forward_ref array
    for (i = 0; i < forward_ref_len; i++)
    {
        if (strcmp(forward_ref[i].label, label) == 0)
        {
            struct LocationPtr *temp = forward_ref[i].head;
            while (temp->next != NULL)
                temp = temp->next;

            // Add the newLocationPtr to end of linkedList
            temp->next = newLocationPtr;
            break;
        }
    }

    // Create a new one if it doesn't exist
    if (i == forward_ref_len)
    {
        strcpy(forward_ref[i].label, label);
        forward_ref[i].head = newLocationPtr;
        forward_ref_len++;
    }
}

int checkAndRemoveForwardRef(char label[40], int location, FILE *temp_ptr, FILE *record_ptr, int *text_len, int *text_starting_addr)
{
    for (int i = 0; i < forward_ref_len; i++)
    {
        if (strcmpi(forward_ref[i].label, label) == 0)
        {
            // Write the current text record which was in temp.txt
            writeTextRecord(temp_ptr, record_ptr, text_len, text_starting_addr, location);

            struct LocationPtr *temp = forward_ref[i].head;
            while (temp != NULL) // Start from head as we want its value too. (Not temp-> next !=NULL)
            {
                fprintf(record_ptr, "\nT^%06X^%02X^%X", temp->location, 2, location); // Write to record ptr. Adderess size will always be 2
                temp = temp->next;
            }

            break;
        }
    }
}

void main()
{
    FILE *pgm_ptr, *optab_ptr, *record_ptr, *temp_ptr, *symtab_ptr;
    int location_ctr = 0, text_len = 0, text_starting_addr = -1, program_obj_staring_addr = -1, program_starting_addr;

    record_ptr = fopen("op/record.txt", "w");
    temp_ptr = fopen("op/temp.txt", "w");
    symtab_ptr = fopen("op/symtab.txt", "w");
    pgm_ptr = fopen("input/source_code.txt", "r");

    printf("Reading Optab\n");
    optab_ptr = fopen("input/optab.txt", "r");
    while (fscanf(optab_ptr, "%s%X", optab[optab_len].opcode, &optab[optab_len].value) != EOF)
        optab_len++;

    printf("Reading Program\n");
    printf("Generating record.txt\n");
    printf("Generating symtab.txt\n");

    while (fscanf(pgm_ptr, "%s%s%s", pgm.label, pgm.opcode, pgm.operand) != EOF)
    {
        pgm.address = location_ctr; // This holds the location addr of current instruction.

        // S1: Calculate next location counter and generate symtab (Similar to 1 Pass)--------------------

        if (strcmp(pgm.opcode, "START") == 0)
        {
            location_ctr = strtol(pgm.operand, NULL, 16);
            program_starting_addr = strtol(pgm.operand, NULL, 16);
            pgm.address = location_ctr; // We need to replace this because its value was at operand. (Initial value of location_ctr is 0x0)
        }
        else if (searchOptab(pgm.opcode) != -1 || strcmp(pgm.opcode, "WORD") == 0)
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
                location_ctr += (strlen(pgm.operand) - 3) / 2;
            else if (pgm.operand[0] == 'C')
                location_ctr += (strlen(pgm.operand) - 3);
        }
        else if (strcmp(pgm.opcode, "END") == 0)
        {
        }
        else
        {
            printf("\nERROR: INVALID OPCODE, %s", pgm.opcode);
            continue;
        }

        // Adding to symtab
        if (searchSymtab(pgm.label) == -1 && !(strcmp(pgm.label, "**") == 0))
        {
            checkAndRemoveForwardRef(pgm.label, pgm.address, temp_ptr, record_ptr, &text_len, &text_starting_addr);
            strcpy(symtab[symtab_len].label, pgm.label);
            symtab[symtab_len].value = pgm.address;

            // Write to symtab.txt
            fprintf(symtab_ptr, "%-7s %6X\n", symtab[symtab_len].label, symtab[symtab_len].value);

            symtab_len++;
        }
        else if (!(strcmp(pgm.label, "**") == 0))
        {
            printf("ERROR: DUPLICATE LABEL, %s\n", pgm.label);
        }

        // S1: ENDS ----------------------------------------------------------------------------------------

        // S2: Writing to record file (Similar to 2 Pass)-------------------------------------------
        if (strcmp(pgm.opcode, "START") == 0)
        {
            fprintf(record_ptr, "H^%6.6s^%06s^%06X", pgm.label, pgm.operand, 0x0);
        }
        else if (searchOptab(pgm.opcode) != -1)
        {
            checkTextRecordLimit(temp_ptr, record_ptr, &text_len, &text_starting_addr, 3, pgm.address, &program_obj_staring_addr);

            int op_pos = searchOptab(pgm.opcode);
            int sym_pos = searchSymtab(pgm.operand);

            if (sym_pos != -1)
            {
                fprintf(temp_ptr, "^%02X%X", optab[op_pos].value, symtab[sym_pos].value);
            }

            // Index Addressing
            else if (strstr(pgm.operand, ",X"))
            {
                char label[40] = "";
                strncpy(label, pgm.operand, strlen(pgm.operand) - 2);

                int sym_pos = searchSymtab(label);

                if (sym_pos != -1)
                {
                    int value = symtab[sym_pos].value + 0x8000;
                    fprintf(temp_ptr, "^%02X%X", optab[op_pos].value, value);
                }
                else
                {
                    // Symbol not found in symtab case
                    fprintf(temp_ptr, "^%02X%04X", optab[op_pos].value, 0x0);
                    addToForwardRef(pgm.operand, pgm.address);
                }
            }

            else
            {
                // Symbol not found in symtab case
                fprintf(temp_ptr, "^%02X%04X", optab[op_pos].value, 0x0);
                addToForwardRef(pgm.operand, pgm.address);
            }

            text_len += 3;
        }
        else if (strcmp(pgm.opcode, "BYTE") == 0)
        {
            float temp_len = 0;
            for (int i = 0; i < strlen(pgm.operand); i++)
            {
                if (pgm.operand[i] == 'C' || pgm.operand[i] == 'X' || pgm.operand[i] == '\'')
                    continue;

                // THIS IS A BUG to be fixed in previous programs
                if (pgm.operand[0] == 'C')
                    temp_len += 2;
                else if (pgm.operand[0] == 'X')
                    temp_len += 1;
            }

            checkTextRecordLimit(temp_ptr, record_ptr, &text_len, &text_starting_addr, temp_len / 2, pgm.address, &program_obj_staring_addr);

            fprintf(temp_ptr, "%s", "^");
            for (int i = 0; i < strlen(pgm.operand); i++)
            {
                if (pgm.operand[i] == 'C' || pgm.operand[i] == 'X' || pgm.operand[i] == '\'')
                    continue;

                if (pgm.operand[0] == 'X')
                    fprintf(temp_ptr, "%C", pgm.operand[i]);
                else if (pgm.operand[0] == 'C')
                    fprintf(temp_ptr, "%X", pgm.operand[i]);
            }

            text_len += temp_len / 2;
        }
        else if (strcmp(pgm.opcode, "WORD") == 0)
        {
            checkTextRecordLimit(temp_ptr, record_ptr, &text_len, &text_starting_addr, 3, pgm.address, &program_obj_staring_addr);
            fprintf(temp_ptr, "^%06X", strtol(pgm.operand, NULL, 10));
            text_len += 3;
        }

        // FOR DEBUG : uncomment following to print address of each instruction
        // printf("%X %7s %7s %7s\n", pgm.address, pgm.label, pgm.opcode, pgm.operand);

        // S2: ENDS ---------------------------------------------------------------------------------
    }

    if (text_len != 0)
        writeTextRecord(temp_ptr, record_ptr, &text_len, &text_starting_addr, pgm.address);

    fprintf(record_ptr, "\nE^%06X", program_obj_staring_addr);

    printf("Computing Program Length");
    int program_length = location_ctr - program_obj_staring_addr;
    fseek(record_ptr, 16, SEEK_SET); // Moving file pointer of record.txt to location of program_length which is at 16th postion
    fprintf(record_ptr, "%06X", program_length);

    fclose(pgm_ptr);
    fclose(optab_ptr);
    fclose(symtab_ptr);
    fclose(record_ptr);
    fclose(temp_ptr);

    printf("\nRemoving temp file");
    remove("op/temp.txt");

    printf("\n\nOne Pass Assembler done...");
}