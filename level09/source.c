#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_msg
{
	char msg[140];
	char username[40];
	size_t size;
} t_msg;

void secret_backdoor()
{
	// 128 bytes reserved: 0xffffffffffffff80 = -128, so "add $0xffffffffffffff80,%rsp" is equivalent to "sub 0x80,%rbp"

	char buf[128];												// at -0x80(%rbp)

	fgets(buf, 128, stdin);										// secret_backdoor+8 - secret_backdoor+33
	system(buf);												// secret_backdoor+38 - secret_backdoor+45
	return ;													// secret_backdoor+50 - secret_backdoor+51
}

void set_username(t_msg* message)
{
	// 160 bytes reserved | message at -0x98(%rbp)

	char buf[128];												// at -0x90(%rbp)

	bzero(buf, 128);											// set_username+18 - set_username+44
	puts(">: Enter your username");								// set_username+47 - set_username+54
	printf(">>: ");												// set_username+59 - set_username+74
	fgets(buf, 128, stdin);										// set_username+79 - set_username+107
	for (int i = 0; i <= 40 && buf[i]; i++)						// set_username+112 - set_username+119 & set_username+153 - set_username+178
		message->username[i] = buf[i];							// set_username+121 - set_username+146
	printf(">: Welcome, %s", message->username);				// set_username+180 - set_username+212
	return ;													// set_username+217 - set_username+218
}

void set_msg(t_msg* message)
{
	// 1040 bytes reserved | message address at -0x408(%rbp)

	char buf[1024];												// at -0x400(%rbp)

	bzero(buf, 1024);											// set_msg+18 - set_msg+44
	puts(">: Msg @Unix-Dude");									// set_msg+47 set_msg+54
	printf(">>: ");												// set_msg+59 - set_msg+74
	fgets(buf, 1024, stdin);									// set_msg+79 - set_msg+107
	strncpy(message->msg, buf, message->size);					// set_msg+112 - set_msg+148
	return ;													// set_msg+153 - set_msg+154
}

void handle_msg()
{
	// 192 bytes reserved
	t_msg message;												// at -0xc0(%rbp)

	messagge.size = 140;										// handle_msg+63
	set_username(&message);										// handle_msg+70 - handle_msg+80
	set_msg(&message);											// handle_msg+85 - handle_msg+95
	puts(">: Msg sent!");										// handle_msg+100 - handle_msg+107
	return ;													// handle_msg+112 - handle_msg+113
}

int main(void)
{
	puts(	"--------------------------------------------\n"
			"|   ~Welcome to l33t-m$n ~    v1337        |\n"
			"--------------------------------------------\n");	// main+4 - main+11
	handle_msg();												// main+16
	return (0);													// main+21 - main+27
}