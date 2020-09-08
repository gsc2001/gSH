#include "echo.h"
#include "utils.h"

void echo(Command c)
{
    for (int i = 0; i < c.argc - 1; i++)
        printf("%s ", c.args[i]);
    printf("%s", c.args[c.argc - 1]);
    if (c.bg)
    {
        printf(" &");
    }
    printf("\n");
}