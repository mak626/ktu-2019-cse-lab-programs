#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct
{
    int line_no;
    char type[50];
    char token[50];
} table[10000];

int table_len = 0;

char *char_to_str(char ch)
{
    char *temp = (char *)malloc(sizeof(char) * 2);
    sprintf(temp, "%c", ch);
    return temp;
}

struct returnParams
{
    bool valid;
    int index;
    char str[200];
};

void insert(int line_no, char type[50], char lex[50])
{
    table[table_len].line_no = line_no;
    strcpy(table[table_len].type, type);
    strcpy(table[table_len].token, lex);

    table_len++;
}

bool isSeparator(char ch)
{
    char test[] = ";[]{}()";

    for (int i = 0; i < strlen(test); ++i)
    {
        if (ch == test[i])
            return true;
    }

    return false;
}

struct returnParams isKeyword(int index, char str[])
{
    char test[][40] = {"printf", "double", "float", "void", "else", "main", "for", "int", "if"}; // order this in desc(strlen())
    int tests_len = 9;
    int maxLen = 6 + 1; // +1 for empty char check. 6 is length of printf

    char buffer[40] = "";
    strncpy(buffer, str + index, maxLen);

    char result[40] = "";
    bool found = true;

    for (int i = 0; i < tests_len; i++)
    {
        found = true;
        for (int j = 0; j < strlen(test[i]); j++)
        {
            if (test[i][j] != buffer[j])
            {
                found = false;
                break;
            }
        }

        if (found == true)
        {
            strcpy(result, test[i]);
            break;
        }
    }

    int rindex = 0;

    if (found && (buffer[strlen(result)] == ' ' || buffer[strlen(result)] == '('))
        rindex = index + strlen(result) - 1;
    else
        found = false;

    struct returnParams r;
    r.valid = found;
    r.index = rindex;
    strcpy(r.str, result);

    return r;
}

struct returnParams isIdentifier(int index, char str[])
{
    struct returnParams r;
    r.valid = false;

    if ((isalpha(str[index]) || str[index] == '_') == 0) // Not starting with alphabet or _
        return r;

    bool found = true;
    int i = 0;

    for (i = index + 1; i < strlen(str); ++i)
    {
        char ch = str[i];

        if (ch == ' ' || ch == ';' || ch == '(' || ch == ')')
            break;
        else if (isalnum(ch) || ch == '_')
            continue;
        else
        {
            found = false;
            break;
        }
    }

    r.valid = found;
    strncpy(r.str, str + index, i - index);
    r.index = i - 1;

    return r;
}

struct returnParams isOperator(char ch, char ch_n, int index)
{
    char str[50] = "";
    sprintf(str, "%c", ch);

    bool found = false;

    // Equal combinations: <=, >=, +=, -= ...
    char test[] = "+-*/=<>!";
    for (int i = 0; i < strlen(test); ++i)
    {
        if (ch == test[i])
        {
            if (ch_n == '=')
                sprintf(str, "%c%c", ch, ch_n);
            else
                sprintf(str, "%c", ch);
            found = true;
        }
    }

    // Logical AND, OR
    if (!found)
    {
        if (ch == '&' || ch == '|')
        {
            if (ch_n == ch)
                sprintf(str, "%c%c", ch, ch_n);
            else
                sprintf(str, "%c", ch);
            found = true;
        }
    }

    // Single operator
    if (!found)
    {
        char test1[] = "%^";
        for (int i = 0; i < strlen(test1); ++i)
        {
            if (ch == test1[i])
            {
                sprintf(str, "%c", ch);
                found = true;
            }
        }
    }

    struct returnParams r;
    r.valid = found;
    r.index = index + strlen(str) - 1;
    strcpy(r.str, str);

    return r;
}

struct returnParams isConstant(int index, char str[])
{
    struct returnParams r;
    r.valid = false;

    if (str[index] != '"')
        return r;

    bool found = false;
    int i = 0;
    for (i = index + 1; i < strlen(str); ++i)
    {
        if (str[i] == '"')
        {
            found = true;
            break;
        }
    }

    r.valid = found;

    strncpy(r.str, str + index + 1, i - index - 1); // INDEX+1 & INDEX-1 to avoid trailing "
    r.index = i;

    return r;
}

struct returnParams isNumber(int index, char str[])
{
    struct returnParams r;
    r.valid = false;

    if (!isdigit(str[index])) // Not a digit
        return r;

    bool found = true;
    bool decimalFound = false;
    bool exponentFound = false;
    int i = 0;

    for (i = index + 1; i < strlen(str); ++i)
    {
        char ch = str[i];

        if (ch == '.')
        {
            if (!decimalFound && !exponentFound)
                decimalFound = true;
            else // Two decimals found || exponent before decimal
            {
                found = false;
                break;
            }
        }
        else if (ch == 'e')
        {
            if (!exponentFound)
                exponentFound = true;
            else // Two exponent found
            {
                found = false;
                break;
            }
        }
        else if (ch == ' ' || ch == ';' || ch == ')')
            break;
        else if (isdigit(ch))
            continue;
        else
        {
            found = false;
            break;
        }
    }

    r.valid = found;

    strncpy(r.str, str + index, i - index);
    r.str[i - index] = '\0';
    r.index = i;

    return r;
}

void main()
{
    FILE *f_ptr;
    f_ptr = fopen("input.c", "r");

    char *str = NULL;
    size_t len = 0;

    int line_no = 0;
    char ch, ch_n, buffer[500];
    struct returnParams r;

    while (getline(&str, &len, f_ptr) != -1)
    {
        line_no++;

        for (int i = 0; i < strlen(str); ++i)
        {
            ch = str[i];
            ch_n = (i + 1 != strlen(str)) ? str[i + 1] : '\0'; // \0 because isOperator() won't match the 2nd char accidentally

            if (ch == '\t' || ch == ' ')
                continue;

            // Comment
            if (ch == '/' && ch_n == '/')
            {
                strncpy(buffer, str + i, strlen(str) - i + 1); // i -> strlen() is comment
                printf("Skipping Comment: %s", buffer);
                break; // the entire line is proccessed
            }

            else if (isSeparator(ch))
            {
                insert(line_no, "SEPERATOR", char_to_str(ch));
                continue;
            }

            r = isOperator(ch, ch_n, i);
            if (r.valid)
            {
                i = r.index;
                insert(line_no, "OPERATOR", r.str);
                continue;
            }

            r = isConstant(i, str);
            if (r.valid)
            {
                i = r.index;
                insert(line_no, "LITERAL", r.str);
                continue;
            }

            r = isNumber(i, str);
            if (r.valid)
            {
                i = r.index;
                insert(line_no, "NUMBER", r.str);
                continue;
            }

            r = isKeyword(i, str);
            if (r.valid)
            {
                i = r.index;
                insert(line_no, "KEYWORD", r.str);
                continue;
            }

            r = isIdentifier(i, str);
            if (r.valid)
            {
                i = r.index;
                insert(line_no, "IDENTIFIER", r.str);
                continue;
            }

            // printf("Invalid character: %c", ch);
        }
    }

    FILE *optr = fopen("output.txt", "w");
    fprintf(optr, "%-3s | %-8s | %-10s | %-10s\n", "ID", "Line No.", "Type", "Token");
    fprintf(optr, "---------------------------------------\n");

    int id = -1;
    for (int i = 0; i < table_len; i++)
    {
        if (strcmp(table[i].type, "IDENTIFIER") == 0)
        {
            ++id;
            fprintf(optr, "%-3d | %-8d | %-10s | %-10s\n", id, table[i].line_no, table[i].type, table[i].token);
        }
        else
        {
            fprintf(optr, "%-3c | %-8d | %-10s | %-10s\n", '-', table[i].line_no, table[i].type, table[i].token);
        }
    }

    fclose(f_ptr);
    fclose(optr);

    printf("Compilation Done..\n");
}
