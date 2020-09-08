#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char str[] = ";;";
    char *t = strtok(str, ";");
    if (t == NULL)
        printf("Yups");
    else
    {
        printf("nopes");
    }
}
