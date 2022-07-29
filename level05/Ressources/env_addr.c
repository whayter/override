#include <stdlib.h>
#include <stdio.h>

int main(int ac, char** av)
{
    if (ac == 2)
        printf("%p\n", av[1]);
    return(0);
}