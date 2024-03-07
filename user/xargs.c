#include "kernel/param.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

char *readline()
{
    char *buf = malloc(1024 * sizeof(char));
    int n = 0;
    while (read(0, buf + n, 1))
    {
        if (n == 1023)
        {
            fprintf(2, "argument is too long\n");
            exit(1);
        }
        if (buf[n] == '\n')
        {
            break;
        }
        ++n;
    }
    buf[n] = 0;
    return buf;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "usage: xargs command\n");
        exit(1);
    }
    char *cmd = argv[1];
    char *args[argc];
    for (int i = 1; i < argc; i++)
    {
        args[i - 1] = argv[i];
    }
    args[argc - 1] = 0;
    char *offset;
    offset = malloc(1024);
    strcpy(offset, readline());
    while (strcmp(offset, ""))
    {
        // printf("%s\n", offset);
        args[argc - 1] = offset;
        if (fork() == 0)
        {
            exec(cmd, args);
            fprintf(2, "exec failed\n");
            exit(1);
        }
        wait(0);
        strcpy(offset, readline());
    }
    exit(0);
}
