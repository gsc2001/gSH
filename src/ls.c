#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "ls.h"
#include "errorHandler.h"
#include "utils.h"

char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
mode_t permissionsMasks[] = {
    S_IRUSR,
    S_IWUSR,
    S_IXUSR,
    S_IRGRP,
    S_IWGRP,
    S_IXGRP,
    S_IROTH,
    S_IWOTH,
    S_IXOTH,
};
struct passwd *user_struct;
struct group *group_struct;
struct tm *mtime;
struct stat statBuf;

void lsExec(Command c)
{
    exitCode = 0;
    LsOpts lsopts;
    lsopts.l = 0, lsopts.a = 0;
    int nFlags = noOfFlags(c.args, c.argc);
    for (int i = 0; i < c.argc; i++)
    {
        if (c.args[i][0] == '-')
        {
            if (c.args[i][1] == 'l' && (strlen(c.args[i]) == 2))
                lsopts.l = 1;
            else if (c.args[i][1] == 'a' && (strlen(c.args[i]) == 2))
                lsopts.a = 1;
            else if (((c.args[i][1] == 'a' && c.args[i][2] == 'l') || (c.args[i][1] == 'l' && c.args[i][2] == 'a')) && strlen(c.args[i]) == 3)
            {
                lsopts.a = 1;
                lsopts.l = 1;
            }
            else
            {
                fprintf(stderr, "ls: Unknown option %s; Usage ls [-l] [-a] dir1 dir2 ...\n", c.args[i]);
                exitCode = 1;
                return;
            }
        }
    }

    if (c.argc == nFlags)
        ls(".", lsopts);
    if (c.argc == nFlags + 1)
    {
        // one dir with flags
        for (int i = 0; i < c.argc; i++)
        {
            if (c.args[i][0] != '-')
            {
                ls(c.args[i], lsopts);
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < c.argc; i++)
        {
            if (c.args[i][0] != '-')
            {
                printf("\n%s:\n", c.args[i]);
                ls(c.args[i], lsopts);
            }
        }
    }
}

int hidden(const struct dirent *item)
{
    return item->d_name[0] != '.';
}

unsigned long getTotalSize(struct dirent **items, int nItems, char *path)
{
    unsigned long sz = 0;
    char *fileName = (char *)malloc(MAX_LEN);
    fileName[0] = '\0';
    for (int i = 0; i < nItems; i++)
    {
        struct dirent *item = items[i];
        strcpy(fileName, path);
        strcat(fileName, "/");
        strcat(fileName, item->d_name);

        struct stat stat_buf;

        handleSyscallint(lstat(fileName, &stat_buf), item->d_name);
        sz += stat_buf.st_blocks;
    }

    free(fileName);
    return sz;
}

void printLslItem(struct dirent *item, char *path)
{

    char *file_path = (char *)malloc(MAX_LEN);
    file_path[0] = '\0';
    strcpy(file_path, path);
    strcat(file_path, "/");
    strcat(file_path, item->d_name);
    handleSyscallint(lstat(file_path, &statBuf), item->d_name);
    char perm[] = "----------";
    if (S_ISDIR(statBuf.st_mode))
        perm[0] = 'd';

    for (int i = 0; i < 9; i++)
    {
        if ((statBuf.st_mode & permissionsMasks[i]) != 0)
        {
            switch (i % 3)
            {
            case 0:
                perm[i + 1] = 'r';
                break;
            case 1:
                perm[i + 1] = 'w';
                break;
            case 2:
                perm[i + 1] = 'x';
                break;
            }
        }
    }

    user_struct = getpwuid(statBuf.st_uid);

    group_struct = getgrgid(statBuf.st_gid);

    mtime = localtime(&statBuf.st_mtime);

    char *fileName = (char *)malloc(MAX_LEN);

    if (S_ISDIR(statBuf.st_mode))
        sprintf(fileName, COL_BLU "%s" COL_WHT, item->d_name);
    else
        sprintf(fileName, "%s", item->d_name);

    printf("%s\t%ld\t%s\t%s\t%ld\t%s\t%d\t%02d:%02d\t%s\n",
           perm, statBuf.st_nlink, user_struct->pw_name,
           group_struct->gr_name, statBuf.st_size,
           months[mtime->tm_mon], mtime->tm_mday,
           mtime->tm_hour, mtime->tm_min, fileName);

    free(file_path);
    free(fileName);
}

void ls(char *path, LsOpts lsopts)
{
    path = replaceTilda(path);
    int nItems;
    struct dirent **items;

    if (lsopts.a)
        nItems = handleSyscallint(scandir(path, &items, NULL, alphasort), path);
    else
        nItems = handleSyscallint(scandir(path, &items, hidden, alphasort), path);

    if (nItems < 0)
    {
        exitCode = 1;
        return;
    }

    if (!lsopts.l)
    {
        char *filePath = (char *)malloc(MAX_LEN);
        char *fileName = (char *)malloc(MAX_LEN);
        struct stat stat_buf;
        for (int i = 0; i < nItems; i++)
        {
            filePath[0] = '\0';
            strcpy(filePath, path);
            strcat(filePath, "/");
            strcat(filePath, items[i]->d_name);
            handleSyscallint(lstat(filePath, &stat_buf), items[i]->d_name);
            if (S_ISDIR(stat_buf.st_mode))
                sprintf(fileName, COL_BLU "%s" COL_WHT, items[i]->d_name);
            else
                sprintf(fileName, "%s", items[i]->d_name);
            printf("%s\n", fileName);
        }

        free(filePath);
        free(fileName);
    }
    else
    {
        printf("total %lu\n", getTotalSize(items, nItems, path) / 2);
        for (int i = 0; i < nItems; i++)
            printLslItem(items[i], path);
    }

    for (int i = 0; i < nItems; i++)
        free(items[i]);
    free(items);
}