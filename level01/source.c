#include <stdio.h>
#include <string.h>

char a_user_name[256];                              // at 0x804a020     // size ?

int verify_user_name()
{
    puts("verifying username....\n");               // verify_user_name+8 - verify_user_name+15
    return (strncmp(a_user_name, "dat_wil", 7));    // verify_user_name+20 - verify_user_name+62
}

int verify_user_pass(char* pass)
{
    return (strncmp(pass, "admin", 5));             // verify_user_pass+5 - verify_user_pass+44
}

int main()
{
    char pass[64];                                  // from 0x1c(%esp) to 0x5c(%esp)
    int res;                                        // at 0x5c(%esp)

    bzero(pass, 64);                                // main+11 - main+29
    res = 0;                                        // main+31
    puts("********* ADMIN LOGIN PROMPT *********"); // main+39 - main+46
    printf("Enter Username: ");                     // main+51 - main+59
    fgets(a_user_name, 256, stdin);                 // main+64 - main+88
    res = verify_user_name();                       // main+93 - main+98
    if (res != 0)                                   // main+102 - main+107
    {
        puts("nope, incorrect username...\n");      // main+109 - main+116
        return(1);                                  // main+121 - main+126 && main+223 - main+229
    }
    puts("Enter Password: ");                       // main+128 - main+135
    fgets(pass, 100, stdin);                        // main+140 - main+164
    res = verify_user_pass(pass);                   // main+176 - main+181
    if (res == 0)                                   // main+185 - main+197
    {
        puts("nope, incorrect password...\n");      // main+199 - main+206
        return(1);                                  // main+211 - main+216 && main+223 - main+229
    }
    return(0);                                      // main+218 - main+229
}