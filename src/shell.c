#include "globals.h"

#include "shell.h"
#include "prompt.h"

void init()
{
    HOME = (char *)malloc(MAX_LEN);
    if (!getcwd(HOME, MAX_LEN))
        perror("Getting Home directory");
}

void listen()
{
    size_t inpsize;
    char *inp = 0;
    size_t bufsize = 0;

    while (1)
    {
        char *prompt = get_prompt();
        printf("%s", prompt);
        inpsize = getline(&inp, &bufsize, stdin);
        if (inpsize < 0)
            break;
        printf("%s", inp);
    }
}