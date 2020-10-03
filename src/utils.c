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
            path[1] = '\0';
            strcpy(path + 1, str + homeLen);
            free(str);
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

int noOfFlags(char **args, int n)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (args[i][0] == '-' && (strlen(args[i]) > 1))
            cnt++;
    }
    return cnt;
}

void initProcess(Process *loc, pid_t pid, char *name)
{
    loc->id = pid;
    loc->name = (char *)malloc(strlen(name) + 1);
    loc->name[0] = '\0';
    strcpy(loc->name, name);
}

int checkEmpty(char *token)
{
    int l = strlen(token);
    for (int i = 0; i < l; i++)
    {
        if (token[i] != ' ')
            return 0;
    }

    return 1;
}

int splitString(char **strs, char *str, char *delim)
{
    int n = 0;
    char *token = strtok(str, delim);
    while (token)
    {
        if (!checkEmpty(token))
        {
            strs[n] = (char *)malloc(strlen(token) + 1);
            strcpy(strs[n++], token);
        }
        token = strtok(NULL, delim);
    }
    free(token);
    return n;
}
