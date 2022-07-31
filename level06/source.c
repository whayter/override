#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int auth(char* login, unsigned int serial)
{
    size_t len;                                                     // at -0xc(%ebp)
    int pwd;                                                        // at -0x10(%ebp)
    int i;                                                          // at -0x14(%ebp)

    login[strcspn(login, "\n")] = '\0';                             // auth+6 - auth+28
    len = strnlen(login, 32);                                       // auth+31 - auth+50
    if (len <= 5)                                                   // auth+53 - auth+66
        return(1);                                                  // auth+68 - auth+73 & auth+303 - auth+304 
    if (ptrace(PTRACE_TRACEME, 1, NULL, NULL) == -1)                // auth+78 - auth+117
    {
        puts("\033[32m.---------------------------.");              // auth+119 - auth+126
        puts("\033[31m| !! TAMPERING DETECTED !!  |");              // auth+131 - auth+138
        puts("\033[32m'---------------------------'");              // auth+143 - auth+150
        return(1);                                                  // auth+155 - auth+160 & auth+303 - auth+304
    }
    pwd = ((int)login[3] ^ 0x1337) + 0x5eeded;                      // auth+165 - auth+187
    i = 0;                                                          // auth+190
    while (i < len)                                                 // auth+275 - auth+281
    {
        if (login[i] <= 31)                                         // auth+199 - auth+210
            return(1);                                              // auth+212 - auth+217 & auth+303 - auth+304
        pwd += ((int)login[i] ^ pwd) % 0x539;                       // auth+219 - auth+268
        i++;                                                        // auth+271
    }
    if (pwd != serial)                                              // auth+283 - auth+289
        return(1);                                                  // auth+291 - auth+296 & auth+303 - auth+304
    return(0);                                                      // auth+298 - auth+304
}

int main(void)
{
    char login[32];                                                 // at 0x2c(%esp)
    unsigned int serial;                                            // at 0x28(%esp)

    puts("***********************************");                    // main+37 - main+44
    puts("*\t\tlevel06\t\t  *");                                    // main+49 - main+56
    puts("***********************************");                    // main+61 - main+68
    printf("-> Enter Login: ");                                     // main+73 - main+81
    fgets(login, 32, stdin);                                        // main+86 - main+110
    puts("***********************************");                    // main+115 - main+122
    puts("***** NEW ACCOUNT DETECTED ********");                    // main+127 - main+134
    puts("***********************************");                    // main+139 - main+146
    printf("-> Enter Serial: ");                                    // main+151 - main+159
    scanf("%u", &serial);                                           // main+173 - main+180
    if (auth(login, serial) != 0)                                   // main+185 - main+207
        return(1);                                                  // main+240 & main+263 - main+264
    puts("Authenticated!");                                         // main+209 - main+216
    system("/bin/sh");                                              // main+221 - main+228
    return(0);                                                      // main+233 & main+263 - main+264
}