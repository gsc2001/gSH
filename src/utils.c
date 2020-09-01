#include "globals.h"
#include "utils.h"

char *replaceHomeDir(char *str)
{
    size_t len = strlen(str);
    size_t homeLen = strlen(HOME);
    if (len < homeLen)
        return str;
    else
    {
        int match = strncmp(str, HOME, homeLen);
        if (match != 0)
            return str;
        else
        {
            char *path = (char *)malloc(MAX_LEN);
            path[0] = '~';
            strncpy(path + 1, str + homeLen, len - homeLen);
            return path;
        }
    }
}

char *replaceTilda(char *str)
{
    if (str[0] == '~')
    {
        char *path = (char *)malloc(MAX_LEN);
        path[0] = '\0';
        strcpy(path, HOME);
        strcat(path, str + 1);
        return path;
    }
    return str;
}

void replaceTabs(char *str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
        if (str[i] == '\t')
            str[i] = ' ';
}