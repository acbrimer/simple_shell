#include "benny.h"

/**
 * errorNotFound - prints string if command entered does not exist
 * @argv: Name of program
 * @command: command entered that does no exist
 */

void errorNotFound(char *argv, char *command)
{
	char *message;

	message = str_concat(argv, command, ": ");
	message = str_concat(message, "not found\n", ": ");
	write(STDERR_FILENO, message, _strlen(message));
}
