#include "echo.h"
#include "utils.h"

void echo(char *str)
{
    char *_str = (char *)malloc(strlen(str) + 1);
    strcpy(_str, str);
    replaceTabs(_str);
    char *token = strtok(_str, " ");
    token = strtok(NULL, " ");
    while (token)
    {
        printf("%s ", token);
        token = strtok(NULL, " ");
    }
    printf("\n");
    free(_str);
}