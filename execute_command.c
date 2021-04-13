#include "benny.h"

/**
 * execute_command - determines type of cmd and executes or logs error
 * @cmd: command struct
 * @argv: name of program
 *
 * Return: 1 for success
*/

int execute_command(cmd_t *cmd, char *argv, char *cmdBuffer)
{
	char *cmd_path;
	pid_t pid;
	int status, exec;

	cmd_path = get_command_path(cmd, argv);
	if (cmd_path != NULL)
	{
		pid = fork();

		if (pid < 0)
		{
			perror("Error in fork");
			free_cmd_t(cmd);
			free(cmd_path);
			free(cmdBuffer);
			return (errno);
		}
		else if (pid == 0)
		{
			exec = execve(cmd_path, cmd->args, environ);
			if (exec == -1)
			{
				perror("Error in execve");
				free_cmd_t(cmd);
				free(cmd_path);
				free(cmdBuffer);
				return (errno);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			free(cmd_path);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
		free(cmd_path);
	}
	return (1);
}
