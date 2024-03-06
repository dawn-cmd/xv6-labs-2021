#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        fprintf(2, "Lack sleep time parameter!\n");
        exit(1);
    }
    int time = atoi(argv[1]);
    sleep(time);
    exit(0);
}
