#include "benny.h"

/**
 * struct cmd_s - struct for holding info about a command
 * @cmd: name of internal command, executable, or garbage
 * @args: arguments for cmd
 * @out_fd: output file descriptor (default 1)
 * @next_operator: operator for next command in linked node
 * @next_cmd: pointer to next cmd for multiple commands in single line
 *
 * Description: holds all data from parsed cmd string
*/
/*
 * parse_command - reads command string and returns array of 
 * @cmd_str: command string
 *
 * Return: new cmd_t struct with info from string
*/
char **parse_command(char *cmd_str)
{
	int i = 1, a = 0;
	char **cmd_arr;
	cmd_t *cmd = malloc(sizeof(cmd_t));

	if (cmd == NULL)
		return (NULL);
	cmd_arr = _strtow(cmd_str, ' ');
	if (cmd_arr[0])
		cmd->cmd = _strdup(cmd_arr[0]);

	cmd->args = cmd_arr;

	return (cmd);
}
