#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void log_wrapper(FILE* f, char* msg, char* path)
{
	// 304 bytes reserved | f at -0x118(%rbp) | msg at -0x120(%rbp) | path at -0x128(%rbp)

	char buf[256];														// at -0x110(%rbp)

	strcpy(buf, msg);													// log_wrapper+47 - log_wrapper+67
	snprintf(buf + strlen(msg), 255 - strlen(msg), path);				// log_wrapper+72 - log_wrapper+210
	buf[strcspn(buf, "\n")] = '\0';										// log_wrapper+215 - log_wrapper+235
	fprintf(f, "LOG: %s\n", buf);										// log_wrapper+243 - log_wrapper+273
}

int main(int ac, char** av)
{
	// 176 bytes reserved | ac at -0x94(%rbp) | av at -0xa0(%rbp)

	char buf[100];														// at -0x70(%rbp)
	int c;																// at -0x71(%rbp)
	int fd;																// at -0x78(%rbp)
	FILE* file;															// at -0x80(%rbp)
	FILE* logs;															// at -0x88(%rbp)

	if (ac != 2)														// main+50 - main+57
		printf("Usage: %s filename\n", av[0]);							// main+59 - main+85
	logs = fopen("./backups/.log", "w");								// main+90 - main+111
	if (logs == NULL)													// main+118 - main+126
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");			// main+128 - main+148
		exit(1);														// main+151 - main+156
	}
	log_wrapper(logs, "Starting back up: ", av[1]);						// main+161 - main+190
	file = fopen(av[1], "r");											// main+195 - main+225
	if (file == NULL)													// main+229 - main+234
	{
		printf("ERROR: Failed to open %s\n", av[1]);					// main+229 - main+266
		exit(1);														// main+271 - main+276
	}
	strcpy(buf, "./backups/");											// main+281 - main+329
	strncat(buf, av[1], 99 - strlen("./backups/"));						// main+334 - main+397
	fd = open(buf, 0x1b0, 0xc1);										// main+402 - main+429
	if (fd < 0)															// main+432 - main+436
	{
		printf("ERROR: Failed to open ./backups/%s\n", av[1]);			// main+438 - main+470
		exit(1);														// main+475 - main+480
	}
	while (1)															// main+529 - main+531
	{
		if ((c = fgetc(file)) == -1)									// main+509 - main+529
			break ;														// main+531
		write(fd, &c, 1);												// main+485 - main+510
	}
	log_wrapper(logs, "Finished back up ", av[1]);						// main+533 - main+562
	fclose(file);														// main+567 - main+574
	close(fd);															// main+579 - main+584
	return(0);															// main+589 - main+615
}