#include "benny.h"

/**
 * execute_command - determines type of cmd and executes or logs error
 * @cmd: command struct
 *
 * Return: 1 for success
*/
int execute_command(cmd_t *cmd)
{
	char *cmd_path;
	pid_t pid;
	int status, exec;

	cmd_path = get_command_path(*cmd);
	if (cmd_path != NULL)
	{
		pid = fork();

		if (pid < 0)
			perror("Error in fork");
		else if (pid == 0)
		{
			exec = execve(cmd_path, cmd->args, environ);
			if (exec == -1)
				perror("Error in execve");
		}
		else
		{
			wait(&status);
		}
		free(cmd_path);
	}
	return (1);
}
