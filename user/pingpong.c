#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int i = 1;
    int p_l_to_r[2];
    int p_r_to_l[2];
    pipe(p_l_to_r);
    if (fork() == 0)
    {
        close(p_l_to_r[1]);
        read(p_l_to_r[0], &i, sizeof(i));
        printf("%d: received ping\n", getpid());
        close(p_l_to_r[0]);
        pipe(p_r_to_l);
        write(p_r_to_l[1], &i, sizeof(i));
        // printf("%d: send pong\n", getpid());
        close(p_r_to_l[1]);
        exit(0);
    }
    else 
    {
        close(p_l_to_r[0]);
        write(p_l_to_r[1], &i, sizeof(i));
        // printf("%d: send ping\n", getpid());
        close(p_l_to_r[1]);
        wait(0);
        close(p_r_to_l[1]);
        read(p_r_to_l[0], &i, sizeof(i));
        printf("%d: received pong\n", getpid());
        close(p_r_to_l[0]);
        wait(0);
    }
    exit(0);
}
