#include <stdio.h>
#include <string.h>

int main(void)
{
    char username[100];                                                 // at -0x70(%rbp)
    char pass[42];                                                      // at -0xa0(%rbp)
    char password[100];                                                 // at -0x110(%rbp)
    FILE* f;                                                            // at -0x8(%rbp)
    int n;                                                              // at -0xc(%rbp)

    memset(username, 0, 48);                                            // main+28 - main+41
    memset(pass, 0, 20);                                                // main+53 - main+73
    memset(password, 0, 48);                                            // main+85 - main+105
    f = fopen("/home/users/level03/.pass", "r")                         // main+132 - main+153
    if (f == 0)
    {
        fwrite("ERROR: failed to open password file\n", 36, 1, stderr); // main+157 - main+195
        exit(1);                                                        // main+200 - main+205
    }
    n = fread(pass, 41, 1, f);                                          // main+210 - main+242
    pass[strcspn(pass, "\n")] = 0;                                      // main+245 - main+265
    if (n != 41)                                                        // main+273 - main+277
    {
        fwrite("ERROR: failed to read password file\n", 36, 1, stderr); // main+279 - main+310
        fwrite("ERROR: failed to read password file\n", 36, 1, stderr); // main+315 - main+346
        exit(1);                                                        // main+351 - main+356
    }
    fclose(f);                                                          // main+361 - main+368
    puts("===== [ Secure Access System v1.0 ] =====");                  // main+373 - main+378
    puts("/***************************************\\");                 // main+383 - main+388
    puts("| You must login to access this system. |");                  // main+393 - main+398
    puts("\\**************************************/");                  // main+403 - main+408
    printf("--[ Username: ");                                           // main+413 - main+426
    fgets(username, 100, stdin);                                        // main+431 - main+453
    username[strcspn(username, "\n")] = 0;                              // main+458 - main+475
    printf("--[ Password: ");                                           // main+480 - main+493
    fgets(password, 100, stdin);                                        // main+498 - main+523
    password[strcspn(password, "\n")] = 0;                              // main+528 - main+548
    puts("*****************************************");                  // main+556 - main+561
    if (strncmp(pass, password, 41) == 0)                               // main+566 - main+598
    {
        printf("Greetings, %s!\n", username);                           // main+600 - main+620
        system("/bin/sh");                                              // main+625 - main+630
    }
    else
    {
        printf(username);                                               // main+642 - main+654
        puts(" does not have access!");                                 // main+659 - main+664
        exit(1);                                                        // main+669 - main+674
    }
    return(0);                                                          // main+635 - main+641
}



/*

RBP         +
            |   f at        -0x8(%rbp)      =>  -8
            |   n at        -0xc(%rbp)      =>  -12
            |
            |
            |   username at -0x70(%rbp)     =>  -112
            |
            |
            |   pass at     -0xa0(%rbp)     =>  -160
            |
            |
            |
            |
            |   password at -0x110(%rbp)    =>  -272
            |
RSP         -                               =>  -288

*/