#include "benny.h"

/**
 * main - runs shell in interactive and non interactive modes
 * @argc: number of args (voided)
 * @argv: arg values (voided)
 *
 * Return: int always 0
*/
int main(int argc, char **argv)
{
	int check;
	int getline_ret;
	int interact_mode = isatty(STDIN_FILENO);
	size_t cmdBufferLen;
	char *cmdBuffer = NULL;
	cmd_t *cmd;

	(void)argc;

	while (1)
	{
		if (interact_mode)
			printf("BENNY$ ");
		getline_ret = getline(&cmdBuffer, &cmdBufferLen, stdin);
		if (getline_ret == EOF)
		{
			printf("\n");
			exit(0);
		}
		log_cmd("log.txt", cmdBuffer, getline_ret);
		cmdBuffer[getline_ret - 1] = '\0';
		cmd = parse_command(cmdBuffer);
		check = builtin(cmd, cmdBuffer);
		if (check == 0)
			execute_command(cmd, argv[0], cmdBuffer);
		free_cmd_t(cmd);
		if (!interact_mode)
			break;
	}
	free(cmdBuffer);
	return (0);
}
