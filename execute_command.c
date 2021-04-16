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
 * f_error - handles errors for files
 * @err: error message
 * @eno: error number
 * @cmd: command struct
 * @linec: current line in shell
 * @exe: name of argv[0] from main
 * @path: cmd_path to free before returning
 *
 * Return: error number
*/
int f_error(char *err, int eno, cmd_t *cmd, int linec, char *exe, char *path)
{
	char *message, *lcstr;
	int i, t, lcmd = _strlen(cmd->cmd), lerr = _strlen(err);

	lcstr = _itoa(linec);
	message = malloc(_strlen(exe) + _strlen(lcstr) + lcmd + lerr + 8);
	for (i = 0, t = 0; exe[i]; i++, t++)
		message[t] = exe[i];
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
	message[t++] = '\n';
	message[t++] = '\0';
	write(STDERR_FILENO, message, _strlen(message));
	errno = eno;
	free(path);
	free(message);
	free(lcstr);

	return (eno);
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
	char *err_notfound = "not found";
	char *err_xok = "Permission denied";

	cmd_path = get_command_path(cmd);
	if ((check_file_exists(cmd_path) == 0) || (cmd_path == NULL))
		return (f_error(err_notfound, 127, cmd, linec, exename, cmd_path));
	if (access(cmd_path, X_OK) != 0)
		return (f_error(err_xok, 126, cmd, linec, exename, cmd_path));
	if (cmd_path != NULL)
	{
		pid = fork();
		if (pid < 0)
		{
			perror(cmd->cmd);
			free_cmd_vars(cmd, cmd_path, cmdBuffer);
			return (errno);
		}
		else if (pid == 0)
		{
			exec = execve(cmd_path, cmd->args, environ);
			if (exec == -1)
				return (errno);
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
