#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>

void clear_stdin()
{
    char c = 0;                                                 // clear_stdin+6
    
    while (c != -1)                                             // clear_stdin+27 - clear_stdin+31
    {
        c = getchar();                                          // clear_stdin+13
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
    return ;                                                    // prog_timeout+16
}

void decrypt(int n)
{
    char str[] = "Q}|u`sfg~sf{}|a3";                            // decrypt+19 - decrypt+40
    int len = strlen(str);                                      // decrypt+60 - decrypt+101

    for (int i = 0; i < len; i++)                               // decrypt+103 - decrypt+139
        str[i] ^= n;
    if (strncmp(str, "Congratulations!", 17) == 0)              // decrypt+141 - decrypt+179
        system("/bin/sh");                                      // decrypt+181 - decrypt+188
    else
        puts("\nInvalid Password");                             // decrypt+195 - decrypt+202
    return ;                                                    // decrypt+224 - decrypt+230
}

void test(int input, int salt)
{
    salt -= input;                                              // test+6 - test+18
    if (salt > 0 && salt < 22 && (salt < 10 || salt > 15))      // test+21 - test+25
        decrypt(salt);                                          // test+
    else
        decrypt(rand());                                        // test+259 - test+267
    return ;                                                    // test+273 - test+274
}

int main(void)
{
    int n;                                                      // at 0x1c(%esp)

    time(0);                                                    // main+25 - main+30
    srand(0);                                                   // main+30 - main+33
    puts("***********************************");                // main+38 - main+45
    puts("*\t\tlevel03\t\t**");                                 // main+50 - main+57
    puts("***********************************");                // main+62 - main+69
    printf("Password:");                                        // main+74 - main+82
    scanf("%d", &n);                                            // main+87 - main+103

    printf("n = %d\n", n);
    test(n, 0x1337d00d);                                        // main+112 - main+123
    return(0);                                                  // main+128 - main+134
}