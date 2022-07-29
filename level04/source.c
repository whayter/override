#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void clear_stdin()
{
    char c = 0;                                                 // clear_stdin+6
    
    while (c != -1)                                             // clear_stdin+27 - clear_stdin+31
    {
        c = getchar();                                          // clear_stdin+13 - clear_stdin+18
        if (c == 10)                                            // clear_stdin+21 - clear_stdin+25
            break ;
    }
    return ;                                                    // clear_stdin+33 - clear_stdin+34
}

int get_unum()
{
    unsigned int c = 0;                                         // get_unum+6

    fflush(stdout);                                             // get_unum+13 - get_unum+21
    scanf("%u", &c);                                            // get_unum+26 - get_unum+41
    clear_stdin();                                              // get_unum+46
    return(c);                                                  // get_unum+51 - get_unum+55
}

void prog_timeout()
{
    exit(1);                                                    // prog_timeout+1 - prog_timeout+13
    return ;                                                    // prog_timeout+15 - prog_timeout+16
}

void enable_timeout_cons()
{
    signal(14, prog_timeout);                                   // enable_timeout_cons+6 - enable_timeout_cons+21
    alarm(60);                                                  // enable_timeout_cons+26 - enable_timeout_cons+33
    return ;                                                    // enable_timeout_cons+38 - enable_timeout_cons+39
}

int main(void)
{
    pid_t pid;                                                      // at 0xac(%esp)
    long syscall_num;                                               // at 0xa8(%esp)
    int n;                                                          // at 0xa0(%esp)
    char buf[32];                                                   // at 0x20(%esp)
    int status;                                                     // at 0x1c(%esp)

    pid = fork();                                                   // main+14 - main+19
    memset(buf, 0, 32);                                             // main+26 - main+44
    syscall_num = 0;                                                // main+46
    status = 0;                                                     // main+57
    if (pid == 0)                                                   // main+65 - main+73
    {
        prctl(1, 1);                                                // main+75 - main+90
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);                      // main+95 - main+126
        puts("Give me some shellcode, k");                          // main+131 - main+138
        gets(buf);                                                  // main+143 - main+150
    }
    else                                                            // main+160
    {
        while (syscall_num != 11)                                   // main+288 - main+296
        {
            wait(&status);                                          // main+161 - main+168
            n = status;                                             // main+173 - main+177
            if ((n & 127) == 0 || (n & 127) + 1 > 0)                  // main+184 - main+226
            {
                puts("child is exiting...");                        // main+228 - main+235
                return(0);                                          // main+338 - main+349
            }
            syscall_num = ptrace(PTRACE_PEEKUSER, pid, 44, NULL);   // main+242 - main+281
        }
        puts("no exec() for you");                                  // main+302 - main+309
        kill(pid, 9);                                               // main+314 - main+332
    }
    return(0);                                                      // main+338 - main+349
}