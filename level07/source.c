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

int store_number(unsigned int* numbers)
{
	unsigned int number;												// at -0x10(%ebp)
	unsigned int index;													// at -0xc(%ebp)

	number = 0;															// store_number+6
	index = 0;															// store_number+13
	printf(" Number: ");												// store_number+20 - store_number+28
	number = get_unum();												// store_number+33 - store_number+38
	printf(" Index: ");													// store_number+41 - store_number+49
	index = get_unum();													// store_number+54 - store_number+59
	if (index % 3 == 0)													// store_number+62 - store_number+88
	{
		puts(" *** ERROR! ***");										// store_number+103 - store_number+110
		puts("   This index is reserved for wil!");						// store_number+115 - store_number+122
		puts(" *** ERROR! ***");										// store_number+127 - store_number+134
		return(1);														// store_number+139 & store_number+165 - store_number+166
	}
	if (number >> 24 != 183)											// store_number+90 - store_number+101
		numbers[index * 4] = number;									// store_number+146 - store_number+158
	return(0);															// store_number+160 - store_number+166
}

int read_number(unsigned int* numbers)
{
	unsigned int index;													// at -0xc(%ebp)

	index = 0;															// read_number+6
	printf(" Index: ");													// read_number+13 - read_number+21
	index = get_unum();													// read_number+26 - read_number+31
	printf(" Number at data[%u] is %u\n", index, numbers[index << 2]);	// read_number+34 - read_number+64
	return(0);															// read_number+69 - read_number+75
}

int main(int ac, char** av, char** env)
{
    char** e;															// at 0x18(%esp)
	char** args;														// at 0x1c(%esp)
    unsigned int numbers[100];											// at 0x24(%esp)
	int ret;															// at 0x1b4(%esp)
    char command[20];													// at 0x1b8(%esp)

	args = av;															// main+15 - main+18
	e = env;															// main+22 - main+25
	command = NULL;														// main+55
	for (int i = 0; i < 100; i++)										// main+110 - main+128
		numbers[i] = 0;
	for (int i = 0; args[i]; i++)										// main+130 - main+207
        memset(args[i], 0, strlen(args[i]));
	for (int i = 0; e[i]; i++)											// main+209 - main+286
        memset(e[i], 0, strlen(e[i]));
	puts(	"----------------------------------------------------\n"
			"  Welcome to wil's crappy number storage service!   \n"
			"----------------------------------------------------\n"
			" Commands:                                          \n"
			"    store - store a number into the data storage    \n"
			"    read  - read a number from the data storage     \n"
			"    quit  - exit the program                        \n"
			"----------------------------------------------------\n"
			"   wil has reserved some storage :>                 \n"
			"----------------------------------------------------\n");	// main+ 288 - main+295
	while (true)														// main+679
	{
		printf("Input command: ");										// main+300 - main+308
		ret = 1;														// main+313
		fgets(command, 20, stdin);										// main+324 - main+351
		if (strncmp(command, "store", 5) == 0)							// main+404 - main+446
			ret = store_number(numbers);								// main+448 - main+467
		else if (strncmp(command, "read", 4) == 0)						// main+469 - main+534
			ret = read_number(numbers);									// main+513 - main+532
		else if (strncmp(command, "quit", 4) == 0)						// main+534 - main+576
			return(0);													// main+684 - main+718
		if (ret == 0)													// main+578 - main+586
			printf(" Failed to do %s command\n", command);				// main+588 - main+607
		else
			printf(" Completed %s command successfully\n", command);	// main+614 - main+633
		command = NULL;													// main+638 - main+645
	}
    return(0);															// main+684 - main+718
}