#include "benny.h"

/**
 * builtin - checks if given command is a built-in
 * @cmd: command struct
 * @cmdBuffer: given command string
 *
 * Return: 1 if builtin, 0 if not
 */

int builtin(cmd_t *cmd, char *cmdBuffer)
{
	char *builtins[] = {"exit", "env", NULL};
	int x;

	if (builtins[0])
	{
		for (x = 0; builtins[x]; x++)
		{
			if (_strcmp(cmd->cmd, builtins[x]) == 0)
			{
				if (x == 0)
					exitFunction(cmd, cmdBuffer);
				if (x == 1)
				{
					printEnv();
					return (1);
				}
			}
		}
	}
	return (0);
}

/**
 * exitFunction - frees and exits if command is exit
 * @cmd: command struct
 * @cmdBuffer: given command string
 */

void exitFunction(cmd_t *cmd, char *cmdBuffer)
{
	free_cmd_t(cmd);
	free(cmdBuffer);
	exit(-1);
}

/**
 * printEnv - prints environ as built-in function
 */

void printEnv(void)
{
	int x;

	for (x = 0; environ[x]; x++)
	{
		write(STDOUT_FILENO, environ[x], _strlen(environ[x]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
