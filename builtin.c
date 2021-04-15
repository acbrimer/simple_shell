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
	char *builtins[] = {"exit", "env", "setenv", "unsetenv", "cd", NULL};
	int x;

	if (builtins[0])
	{
		for (x = 0; builtins[x]; x++)
		{
			if (_strcmp(builtins[x], cmd->cmd) == 0)
			{
				if (x == 0)
					exitFunction(cmd, cmdBuffer);
				if (x == 1)
				{
					printEnv();
					return (1);
				}
				if (x == 2)
				{
					_setenv(cmd->args[1], cmd->args[2], 1);
					return (1);
				}
				if (x == 3)
				{
					_unsetenv(cmd->args[1]);
					return (1);
				}
				if (x == 4)
				{
					cdFunction(cmd);
					return (1);
				}
			}
		}
	}
	return (0);
}

void cdFunction(cmd_t *cmd)
{
	char cwd[1000], *target;

	if (cmd->args == NULL || cmd->args[0] == NULL)
		target = _getenv("HOME");
	else if (_strcmp(cmd->args[1], "-") == 0)
		target = _getenv("HOME");
	else
		target = _strdup(cmd->args[1]);
	printf("Target: %s\n", target);
	chdir(target);
	free(target);
	getcwd(cwd, 1000);
	_setenv("PWD", cwd, 1);
}

/**
 * exitFunction - frees and exits if command is exit
 * @cmd: command struct
 * @cmdBuffer: given command string
 */

void exitFunction(cmd_t *cmd, char *cmdBuffer)
{
	int exitstatus = 0;

	if (cmd->args != NULL && cmd->args[1] != NULL)
		exitstatus = _atoi(cmd->args[1]);
	free_cmd_t(cmd);
	free(cmdBuffer);
	exit(exitstatus);
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
