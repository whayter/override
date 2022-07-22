#include <stdio.h>

int main()
{
    int n;                                                  // esp+1c

    puts("***********************************");            // main+9 - main+ 16
    puts("* \t     -Level00 -\t\t  *");                     // main+21 - main+28
    puts("***********************************");            // main+33 - main+40
    printf("Password:");                                    // main+45 - main+53
    scanf("%d", &n);                                        // main+58 - main+74
    if (n != 5276)                                          // main+79 - main+88
    {
        puts("\nInvalid Password!");                        // main+121 - main+128
        return(-1);                                         // main+133 - main+139
    }
    else
    {
        puts("\nAuthenticated!")                            // main+90 - main+97
        system("/bin/sh");                                  // main+102 - main+109
    }
    return(0);                                              // main+138 - main+139
}