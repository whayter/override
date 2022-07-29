#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    char buf[100];                                                  // at 0x28(%esp)                                        
    int i;                                                          // at 0x8c(%esp)

    i = 0;                                                          // main+14
    fgets(buf, 100, stdin);                                         // main+25 - main+49
    i = 0;                                                          // main+54
    while (buf[i])                                                  // main+143 - main+186
    {
        if (buf[i] > 64 && buf[i] <= 90)                            // main+67 - main+101
            buf[i] += 32;                                           // main+103 - main+133
        i++;                                                        // main+135
    }
    printf(buf);                                                    // main+188 - main+195
    return(exit(0));                                                // main+200 - main+207
}