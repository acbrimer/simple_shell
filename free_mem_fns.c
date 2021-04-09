#include "benny.h"

/**
 * free_str_array - frees array of strings
 * @arr: array to be freed
 *
 * Return: NULL
 */

char **free_str_array(char **arr)
{
	int i;

	for (i = 0; arr[i] != NULL; i++)
		if (arr[i] != NULL)
			free(arr[i]);
	free(arr);
	return ((char **)(NULL));
}

/**
 * free_cmd_t - frees command struct
 * @cmd: struct to be freed
 */

void free_cmd_t(cmd_t *cmd)
{
	if (cmd)
	{
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->args)
			free_str_array(cmd->args);
		free(cmd);
	}
}
