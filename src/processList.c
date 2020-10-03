#include "processList.h"
#include "utils.h"
#include "errorHandler.h"

Node *head = NULL;

Process findProcess(pid_t pid)
{
    Node *i = head;
    Process p = {.id = pid, .name = NULL};
    while (i)
    {
        if (i->p.id == pid)
        {
            initProcess(&p, pid, i->p.name);
            break;
        }
        i = i->prev;
    }
    return p;
}

Process findProcessJobNo(int job_no)
{
    Process p = {.id = -1, .name = NULL};
    Node *i = head;

    if (!i || job_no <= 0)
        return p;
    // roll back
    while (i->prev)
        i = i->prev;

    job_no--;
    while (job_no && i)
    {
        i = i->next;
        job_no--;
    }
    if (i)
        initProcess(&p, i->p.id, i->p.name);
    return p;
}

void insertProcess(Process p)
{
    Node *node = (Node *)malloc(sizeof(Node));
    initProcess(&(node->p), p.id, p.name);
    if (head)
    {
        head->next = node;
        node->prev = head;
        node->next = NULL;
    }
    else
    {
        node->prev = NULL;
        node->next = NULL;
    }
    head = node;
}

void removeProcess(pid_t pid)
{
    Node *i = head;
    while (i)
    {
        if (i->p.id == pid)
            break;
        i = i->prev;
    }

    if (!i)
        return;

    if (i->prev)
        i->prev->next = i->next;
    if (i->next)
        i->next->prev = i->prev;
    if (i == head)
        head = i->prev;

    free(i->p.name);
    free(i);
}

void printProcesses()
{
    char *statusFile = (char *)malloc(MAX_LEN);
    char *buf = (char *)malloc(MAX_LEN);

    // completely roll back
    Node *i = head;
    if (!i)
        return;

    while (i->prev)
        i = i->prev;

    int cur = 1;
    while (i)
    {
        char state;
        Process p = i->p;
        sprintf(statusFile, "/proc/%d/stat", p.id);
        FILE *f = fopen(statusFile, "r");
        int cnt = 1;
        while (fscanf(f, "%s", buf) != EOF)
        {
            if (cnt == 3)
            {
                state = buf[0];
                break;
            }
            cnt++;
        }
        fclose(f);
        if (state == 'T')
            strcpy(buf, "Stopped");
        else
            strcpy(buf, "Running");

        printf("[%d] %s %s [%d]\n", cur, buf, p.name, p.id);

        i = i->next;
        cur++;
    }

    free(statusFile);
    free(buf);
}

void killAllProcesses()
{
    Node *i = head;
    while (i)
    {
        handleSyscallint(kill(i->p.id, SIGINT), "Killing");
        i = i->prev;
    }
}