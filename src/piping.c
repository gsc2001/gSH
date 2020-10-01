#include "piping.h"
#include "shell.h"
#include "errorHandler.h"

void execPiped(PipedCommands piped)
{
    if (piped.n == 1)
    {
        execCommand(piped.commands[0]);
        return;
    }

    int stdinSave = dup(STDIN_FILENO), stdoutSave = dup(STDOUT_FILENO);

    int pipes[piped.n - 1][2];

    for (int i = 0; i < piped.n; i++)
    {
        if (i < piped.n - 1)
            handleSyscallint(pipe(pipes[i]), "Cannot create pipe");

        if (i == 0)
        {
            // inp from STDIN and STDOUT to pipes[0][1]
            dup2(pipes[i][1], STDOUT_FILENO);
            execCommand(piped.commands[i]);
            handleSyscallint(close(pipes[i][1]), "Closing pipe write end");
        }
        else if (i == piped.n - 1)
        {
            // inp from pipes[n-2][0] and out to STDOUT
            dup2(pipes[i - 1][0], STDIN_FILENO);

            dup2(stdoutSave, STDOUT_FILENO);
            execCommand(piped.commands[i]);
            handleSyscallint(close(pipes[i - 1][0]), "Closing pipe read end");
        }
        else
        {
            dup2(pipes[i - 1][0], STDIN_FILENO);
            dup2(pipes[i][1], STDOUT_FILENO);
            execCommand(piped.commands[i]);
            handleSyscallint(close(pipes[i - 1][0]), "Closing pipe read end");
            handleSyscallint(close(pipes[i][1]), "Closing pipe read end");
        }
    }
    // restore stdin stdout
    dup2(stdinSave, STDIN_FILENO);
}
