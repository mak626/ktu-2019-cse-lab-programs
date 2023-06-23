#include <stdio.h>
#include <string.h>

void getDomain(char addr[40], char domainName[40])
{
    int len = 0;
    for (int i = 0; i < strlen(addr); i++)
    {
        if (addr[i] == '@')
        {
            int noDotFoundError = 1;

            for (int j = i + 1; j < strlen(addr); j++)
            {
                if (addr[j] == '.')
                {
                    noDotFoundError = 0;
                    domainName[len++] = '\0';
                    break;
                }
                else
                {
                    domainName[len++] = addr[j];
                }
            }

            if (noDotFoundError == 1)
                strcpy(domainName, "INVALID");

            break;
        }
    }
}

void main()
{
    char mail[40], domainName[40];
    scanf("%s", mail);
    getDomain(mail, domainName);
    printf("%s", domainName);
}