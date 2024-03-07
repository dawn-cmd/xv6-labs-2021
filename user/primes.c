#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

void sub_proc(int p[])
{
    close(p[1]);
    int prime;
    if (read(p[0], &prime, sizeof(prime)) != 4)
    {
        exit(1);
    }
    printf("prime %d\n", prime);
    int num;
    if (read(p[0], &num, sizeof(num)) == 0)
        exit(0);
    int newp[2];
    pipe(newp);
    if (fork() == 0)
    {
        sub_proc(newp);
        exit(0);
    }
    close(newp[0]);
    if (write(newp[1], &num, sizeof(num)) != sizeof(num))
    {
        exit(1);
    }
    while (read(p[0], &num, sizeof(num)))
    {
        if (num % prime == 0)
            continue;
        write(newp[1], &num, sizeof(num));
    }
    close(newp[1]);
    close(p[0]);
    wait(0);
    exit(0);
}

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        sub_proc(p);
        exit(0);
    }
    close(p[0]);
    for (int i = 2; i < 32; ++i)
    {
        if (write(p[1], &i, sizeof(i)) != sizeof(i))
        {
            exit(1);
        }
    }
    close(p[1]);
    wait(0);
    return 0;
}
