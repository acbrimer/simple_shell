#include "benny.h"


void free_str_array(char **arr)
{
	int i;

	for (i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

void free_cmd_t(cmd_t *cmd)
{
	free(cmd->cmd);
	free_str_array(cmd->args);
	free(cmd);
}
