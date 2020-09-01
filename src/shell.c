#include "shell.h"
#include "prompt.h"
#include "parse.h"
#include "mpwd.h"

void init()
{
    HOME = (char *)malloc(MAX_LEN);
    if (!getcwd(HOME, MAX_LEN))
        perror("Getting Home directory");
}
const int builtInN = 1;

const char *builtInComs[] = {
    "pwd",
};

// built in command functions
void (*builtInComExec[])(Command c) = {
    pwdExec,
};

void execCommand(Command c)
{
    int commandIndex = -1;

    for (int i = 0; i < builtInN; i++)
    {
        if (!strcmp(c.cmd, builtInComs[i]))
        {
            commandIndex = i;
            break;
        }
    }

    if (commandIndex != -1)
        builtInComExec[commandIndex](c);
    else
        fprintf(stderr, "%s: Command not found\n", c.cmd);
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
        inp[strlen(inp) - 1] = ';';
        // parse inp
        ParsedCommands parsed = parse(inp);
        for (int i = 0; i < parsed.n; i++)
            execCommand(parsed.commands[i]);
        if (DEBUG)
        {
            fprintf(stderr, "\n\n\n\n===========DEBUG===========\n");

            fprintf(stderr, "n=%d", parsed.n);
            for (int i = 0; i < parsed.n; i++)
            {
                Command com_ = parsed.commands[i];
                fprintf(stderr, "\n---------------------------------------\n");
                fprintf(stderr, "cmd = %s; flags=%s; argc=%d\n", com_.cmd, com_.flags, com_.argc);
                fprintf(stderr, "Args -> ");
                for (int j = 0; j < com_.argc; j++)
                    fprintf(stderr, "%s,", com_.args[j]);
                fprintf(stderr, "\n----------------------------------------\n");
            }
            fprintf(stderr, "==========================\n\n\n\n");
        }
    }
}