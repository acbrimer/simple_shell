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
	int interact_mode = isatty(STDIN_FILENO);
	size_t cmdBufferLen;
	char *cmdBuffer = NULL;
	cmd_t *cmd;

	(void)argc;

	while (1)
	{
		if (interact_mode)
			printf("BENNY$ ");
		cmdBufferLen = getline(&cmdBuffer, &cmdBufferLen, stdin);
		log_cmd("log.txt", cmdBuffer, cmdBufferLen);
		cmdBuffer[cmdBufferLen - 1] = '\0';
		cmd = parse_command(cmdBuffer);
		check = builtin(cmd, cmdBuffer);
		if (check == 0)
			execute_command(cmd, argv[0]);
		free_cmd_t(cmd);
		if (!interact_mode)
			break;
	}
	free(cmdBuffer);
	return (0);
}
