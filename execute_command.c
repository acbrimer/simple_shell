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
 * file_not_found_error - prints error for file not found
 * @cmd: command struct
 * @linecounter: current line in shell
 * @exename: name of shell
 *
 * Return: int error code
*/
int file_not_found_error(cmd_t *cmd, int linecounter, char *exename)
{
	char *message, *err = "not found\n", *lcstr;
	int i, t;

	lcstr = _itoa(linecounter);
	message = malloc(_strlen(exename) + _strlen(lcstr) + _strlen(cmd->cmd) + 17);
	for (i = 0, t = 0; exename[i]; i++, t++)
		message[t] = exename[i];
	message[t++] = ':';
	message[t++] = ' ';
	for (i = 0; lcstr[i]; i++, t++)
		message[t] = lcstr[i];
	message[t++] = ':';
	message[t++] = ' ';
	for (i = 0; cmd->cmd[i]; i++, t++)
		message[t] = cmd->cmd[i];
	message[t++] = ':';
	message[t++] = ' ';
	for (i = 0; err[i]; i++, t++)
		message[t] = err[i];
	message[t++] = '\0';
	write(STDERR_FILENO, message, _strlen(message));
	free(lcstr);
	free(message);

	return (0);
}
/**
 * execute_command - determines type of cmd and executes or logs error
 * @cmd: command struct
 * @cmdBuffer: command buffer
 * @linec: linecounter from main
 * @exename: argv[0]
 *
 * Return: 0 if successful
*/
int execute_command(cmd_t *cmd, char *cmdBuffer, int linec, char *exename)
{
	char *cmd_path;
	pid_t pid;
	int status, exec;

	cmd_path = get_command_path(cmd);
	if (check_file_exists(cmd_path) == 0)
	{
		free(cmd_path);
		return (file_not_found_error(cmd, linec, exename));
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
