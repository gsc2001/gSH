#include "list.h"
#include "utils.h"

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
