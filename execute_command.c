#include "benny.h"

/**
 * free_cmd_vars - frees vars from execute_command
 * @cmd: command struct
 * @cmd_path: command path
 * @cmdBuffer: command buffer
*/
void free_cmd_vars(cmd_t *cmd, char *cmd_path, char *cmdBuffer)
{
	if (cmd != NULL)
		free_cmd_t(cmd);
	if (cmd_path != NULL)
		free(cmd_path);
	if (cmdBuffer != NULL)
		free(cmdBuffer);
}

/**
 * check_file_exists - checks if a file exists
 * @path: path to file
 *
 * Return: 1 if exists, else 0
*/
int check_file_exists(char *path)
{
	struct stat *file_stat = malloc(sizeof(struct stat));
	int found_file;

	found_file = stat(path, file_stat);
	free(file_stat);
	return (found_file == 0 ? 1 : 0);
}
/**
 * execute_command - determines type of cmd and executes or logs error
 * @cmd: command struct
 * @argv: name of program
 * @cmdBuffer: command buffer
 *
 * Return: 0 if successful
*/
int execute_command(cmd_t *cmd, char *argv, char *cmdBuffer)
{
	char *cmd_path;
	pid_t pid;
	int status, exec;

	cmd_path = get_command_path(cmd, argv);
	if (check_file_exists(cmd_path) == 0)
	{
		write(STDOUT_FILENO, "file not found :(\n", 18);
		return (0);
	}
	if (cmd_path != NULL)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Error in fork");
			free_cmd_vars(cmd, cmd_path, cmdBuffer);
			return (errno);
		}
		else if (pid == 0)
		{
			exec = execve(cmd_path, cmd->args, environ);
			if (exec == -1)
			{
				perror("Error in execve");
				free(cmd_path);
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
	return (0);
}
