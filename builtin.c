#include "benny.h"

int builtin(cmd_t *cmd)
{
	char *builtins[] = {"exit", "env", NULL};
	int x;

	for (x = 0; builtins[x]; x++)
	{
		if (_strcmp(cmd->cmd, builtins[0]) == 0)
			exitFunction();
		if (_strcmp(cmd->cmd, builtins[1]) == 0)
			printEnv();
	}
	return (0);
}

void exitFunction(void)
{
	_exit(1);
}

void printEnv(void)
{
	int x;

	printf("Builtin\n");

	for (x = 0; environ[x] != NULL; x++)
		printf("%s\n", environ[x]);

}
