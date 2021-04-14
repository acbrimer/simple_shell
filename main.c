#include "benny.h"

/**
 * check_linelen - handler function to check getline return for EOF/error
 * @exename: name of exe
 * @cmdBuffer: command buffer pointer
 * @mode: interactive mode
 * @linelen: linelen returned from getline
*/
void check_linelen(char *exename, char *cmdBuffer, int mode, int linelen)
{
	int errnum = 0;

	if (mode && linelen == -1)
	{
		errnum = errno;
		write(STDOUT_FILENO, "\n", 1);
		free(cmdBuffer);
		if (errnum == 2)
			exit(0);
		perror(exename), exit(errnum);
	}
}
/**
 * main - runs shell in interactive and non interactive modes
 * @argc: number of args (voided)
 * @argv: arg values (voided)
 *
 * Return: int always 0
*/
int main(__attribute((unused))int argc, char **argv)
{
	int check, linelen = 0, i = 0, mode = isatty(STDIN_FILENO);
	size_t cmdBufferLen;
	char *cmdBuffer = NULL;
	cmd_t *cmd;
	int linecounter = 0;

	while (1)
	{
		if (mode)
			write(STDOUT_FILENO, "BENNY$ ", 7);
		while ((linelen = getline(&cmdBuffer, &cmdBufferLen, stdin)) != -1)
		{
			i = 0;
			while (cmdBuffer[i] == ' ')
				i++;
			if (linelen - i == 1)
				break;
			log_cmd("log.txt", (cmdBuffer + i), linelen - i);
			cmdBuffer[linelen - 1] = '\0';
			cmd = parse_command((cmdBuffer + i));
			check = builtin(cmd, (cmdBuffer + i));
			if (check == 0)
				execute_command(cmd, (cmdBuffer + i));
			free_cmd_t(cmd);
			linecounter++;
			if (mode)
				write(STDOUT_FILENO, "BENNY$ ", 7);
		}
		/* helper function to free up lines in main */
		check_linelen(argv[0], cmdBuffer, mode, linelen);
		if (!mode)
			break;
	}
	free(cmdBuffer);
	return (0);
}
