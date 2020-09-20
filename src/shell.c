#include "shell.h"
#include "prompt.h"
#include "parse.h"
#include "mpwd.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "sysCommand.h"
#include "pinfo.h"
#include "errorHandler.h"
#include "signalHandlers.h"
#include "history.h"

void init()
{
    HOME = handleSyscallchar(getcwd(NULL, MAX_LEN - 1), "Getting home dir");

    // load history
    loadHistory();

    // signal handlers
    signal(SIGCHLD, sigchldHandler);
}
const int builtInN = 6;

const char *builtInComs[] = {
    "pwd",
    "cd",
    "ls",
    "pinfo",
    "echo",
    "history",
};

// built in command functions
void (*builtInComExec[])(Command c) = {
    pwdExec,
    cdExec,
    lsExec,
    pinfoExec,
    echo,
    historyExec,
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
    {
        execSys(c);
    }
}

void repl()
{
    size_t inpsize;
    char *inp = 0;
    size_t bufsize = 0;

    while (1)
    {
        char *prompt = get_prompt();
        printf("%s", prompt);
        fflush(stdout);
        inpsize = getline(&inp, &bufsize, stdin);
        if (inpsize < 0)
            break;
        inp[strlen(inp) - 1] = '\0';

        // add to history
        addToHistory(inp);

        char *inpCopy = (char *)malloc(strlen(inp) + 1);
        inpCopy[0] = '\0';
        strcpy(inpCopy, inp);

        // parse inp
        ParsedCommands parsed = parse(inpCopy);
        if (DEBUG)
        {
            fprintf(stderr, "\n\n\n\n===========DEBUG===========\n");
            fprintf(stderr, "n=%d", parsed.n);
            for (int i = 0; i < parsed.n; i++)
            {
                Command com_ = parsed.commands[i];
                fprintf(stderr, "\n---------------------------------------\n");
                fprintf(stderr, "cmd = %s; argc=%d; bg=%d\n", com_.cmd, com_.argc, com_.bg);
                fprintf(stderr, "Args -> ");
                for (int j = 0; j < com_.argc; j++)
                    fprintf(stderr, "%s,", com_.args[j]);
                fprintf(stderr, "\n----------------------------------------\n");
            }
            fprintf(stderr, "==========================\n\n\n\n");
        }
        for (int i = 0; i < parsed.n; i++)
        {
            if (parsed.commands[i].cmd)
            {
                // check if exit
                if (!strcmp(parsed.commands[i].cmd, "exit"))
                {
                    free(prompt);
                    free(parsed.commands);
                    free(inpCopy);
                    return;
                }
                execCommand(parsed.commands[i]);
            }
        }

        //cleanup
        free(parsed.commands);
        free(prompt);
        free(inpCopy);
    }
}

void byebye()
{
    saveHistory();
}
