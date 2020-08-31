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