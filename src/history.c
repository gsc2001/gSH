#include "history.h"
#include "utils.h"
#include "errorHandler.h"

void loadHistory()
{
    // init steps
    hpos = 0;
    histFile = (char *)malloc(strlen(".gsh_history") + 1);
    strcpy(histFile, ".gSH_history");

    // Nullify the full list
    for (int i = 0; i < HISTORY_SZ; i++)
        histList[i] = NULL;

    FILE *histf = fopen(histFile, "r");
    if (histf == NULL)
        return;

    char *buf = (char *)malloc(MAX_LEN);

    while ((fgets(buf, MAX_LEN - 1, histf)))
    {
        buf[strlen(buf) - 1] = '\0';
        if (!strlen(buf))
            continue;
        addToHistory(buf);
    }

    fclose(histf);
    free(buf);
}

void addToHistory(char *command)
{
    if (histList[hpos])
        free(histList[hpos]);
    histList[hpos] = (char *)malloc(strlen(command) + 1);
    strcpy(histList[hpos], command);
    hpos = (hpos + 1) % HISTORY_SZ;
}

void historyExec(Command c)
{
    if (noOfFlags(c.args, c.argc))
        fprintf(stderr, "history does not take any flags; Usage history [n]\n");
    else if (!c.argc)
        history(10);
    else if (c.argc == 1)
        history(atoi(c.args[0]));
    else
        fprintf(stderr, "too many arguments for history; Usage history [n]\n");
}

void history(int max_n)
{
    if (!max_n)
    {
        printf("\n");
        return;
    }
    if (max_n > HISTORY_SZ)
    {
        fprintf(stderr, "argument of history can be at max 20\n");
        return;
    }
    int i = 0;
    int p = (hpos - 1 + HISTORY_SZ) % HISTORY_SZ;
    while (histList[p] && i < max_n)
    {
        p = (p - 1 + HISTORY_SZ) % HISTORY_SZ;
        i++;
    }

    p = (p + 1) % HISTORY_SZ;

    while (i > 0)
    {
        printf("%s\n", histList[p]);
        p = (p + 1) % HISTORY_SZ;
        i--;
    }
}

void saveHistory()
{
    FILE *histf = fopen(histFile, "w");
    if (histf == NULL)
    {
        fprintf(stderr, "Cannot create history file");
        return;
    }

    int p = (hpos - 1 + HISTORY_SZ) % HISTORY_SZ;
    int i = 0;
    while (histList[p] && i < HISTORY_SZ)
    {
        p = (p - 1 + HISTORY_SZ) % HISTORY_SZ;
        i++;
    }

    p = (p + 1) % HISTORY_SZ;

    while (i > 0)
    {
        fprintf(histf, "%s\n", histList[p]);
        p = (p + 1) % HISTORY_SZ;
        i--;
    }

    handleSyscallint(fclose(histf), "Connot save history");

    for (int i_ = 0; i_ < HISTORY_SZ; i_++)
    {
        if (histList[i_])
            free(histList[i_]);
    }
}