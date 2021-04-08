#include "benny.h"

int builtin(cmd_t *cmd, char *cmdBuffer)
{
	char *builtins[] = {"exit", "env", NULL};
	int x;

	for (x = 0; builtins[x]; x++)
	{
		if (_strcmp(cmd->cmd, builtins[0]) == 0)
			exitFunction(cmd, cmdBuffer);
		if (_strcmp(cmd->cmd, builtins[1]) == 0)
			printEnv();
	}
	return (0);
}

void exitFunction(cmd_t *cmd, char *cmdBuffer)
{
	free_cmd_t(cmd);
	free(cmdBuffer);
	_exit(1);
}

void printEnv(void)
{
	int x;

	for (x = 0; environ[x] != NULL; x++)
	{
		write(STDOUT_FILENO, environ[x], _strlen(environ[x]));
	}
}
