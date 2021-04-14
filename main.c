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
	int check, errnum = 0, linelen = 0, i = 0, mode = isatty(STDIN_FILENO);
	size_t cmdBufferLen;
	char *cmdBuffer = NULL;
	cmd_t *cmd;

	(void)argc;
	while (1)
	{
		if (mode)
			printf("BENNY$ ");
		while ((linelen = getline(&cmdBuffer, &cmdBufferLen, stdin)) != -1)
		{
			while (cmdBuffer[i] == ' ')
				i++;
			if (linelen - i == 1)
				break;
			log_cmd("log.txt", (cmdBuffer + i), linelen - i);
			cmdBuffer[linelen - 1] = '\0';
			cmd = parse_command((cmdBuffer + i));
			check = builtin(cmd, (cmdBuffer + i));
			if (check == 0)
				execute_command(cmd, argv[0], (cmdBuffer + i));
			free_cmd_t(cmd);
			if (mode)
				printf("BENNY$ ");
		}
		if (mode && linelen == -1)
		{
			errnum = errno;
			printf("\n");
			free(cmdBuffer);
			if (errnum == 2)
				exit(0);
			perror(argv[0]), exit(errnum);
		}
		if (!mode)
			break;
	}
	free(cmdBuffer);
	return (0);
}
