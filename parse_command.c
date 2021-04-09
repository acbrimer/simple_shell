#include "benny.h"

/**
 * parse_command - reads command string and returns struct
 * @cmd_str: command string
 *
 * Return: new cmd_t struct with info from string
*/
cmd_t *parse_command(char *cmd_str)
{
	char **cmd_arr = _strtow(cmd_str, ' ');
	cmd_t *cmd = malloc(sizeof(cmd_t));

	if (cmd == NULL)
		return (NULL);
	if (cmd_arr[0])
		cmd->cmd = _strdup(cmd_arr[0]);

	cmd->args = cmd_arr;

	return (cmd);
}
