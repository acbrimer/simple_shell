#include "benny.h"


char **free_str_array(char **arr)
{
	int i;

	for (i = 0; arr[i] != NULL; i++)
		if (arr[i] != NULL)
			free(arr[i]);
	free(arr);
	return (char **)(NULL);
}

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
