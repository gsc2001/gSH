#include "parse.h"
#include "utils.h"

Command parseCommand(char *command_raw)
{
    char *command_ = (char *)malloc(strlen(command_raw) + 1);
    command_[0] = '\0';
    strcpy(command_, command_raw);
    Command command;
    command.args = NULL;
    command.flags = NULL;
    command.command_str = (char *)malloc(strlen(command_) + 1);
    strcpy(command.command_str, command_);
    command.cmd = strtok(command_, " ");
    command.argc = 0;
    char *args_[MAX_LEN];
    char *flags = (char *)malloc(MAX_LEN);
    flags[0] = '\0';
    char *arg;

    // loop over args
    while ((arg = strtok(NULL, " ")))
    {
        if (arg[0] == '-')
            strcat(flags, arg + 1);
        else
            args_[command.argc++] = arg;
    }
    command.args = (char **)malloc(command.argc * sizeof(char *));
    for (int i = 0; i < command.argc; i++)
        command.args[i] = args_[i];
    if (strlen(flags))
    {
        command.flags = (char *)malloc(strlen(flags) + 1);
        strcpy(command.flags, flags);
    }
    free(flags);
    return command;
}

ParsedCommands parse(char *inp)
{
    replaceTabs(inp);
    char *commands[MAX_LEN];
    int nCommands = 0;
    commands[nCommands++] = strtok(inp, ";");

    while ((commands[nCommands] = strtok(NULL, ";")))
    {
        nCommands++;
    }

    ParsedCommands parsed;
    parsed.n = nCommands;
    parsed.commands = (Command *)malloc(nCommands * sizeof(Command));
    for (int i = 0; i < nCommands; i++)
    {
        parsed.commands[i] = parseCommand(commands[i]);
    }
    return parsed;
}