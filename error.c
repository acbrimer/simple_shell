#include "benny.h"

/**
 * errorNotFound - prints string if command entered does not exist
 * @argv: Name of program
 * @command: command entered that does no exist
 */

int errorNotFound(char *argv, char *command)
{
	char *message;
	char *message2;

	message = str_concat(argv, command, ": ");
	message2 = str_concat(message, "not found\n", ": ");
	free(message);
	write(STDERR_FILENO, message2, _strlen(message2));
	free(message2);
	return(1);
}
