#include "benny.h"

/**
 * main - runs shell in interactive and non interactive modes
 * @argc: number of args (voided)
 * @argv: arg values (voided)
 * @envp: array of environment vars (voided)
 *
 * Return: int always 0
*/
int main(int argc, char **argv, char **envp)
{
	int run_shell = 1;
	int interact_mode = isatty(STDIN_FILENO);
	size_t cmdBufferLen;
	char *cmdBuffer = NULL;
	cmd_t *cmd;
	char *cmd_path;

	(void)argc;
	(void)argv;
	environ = envp;
	while (1)
	{
		if (interact_mode)
			printf("BENNY$ ");
		cmdBufferLen = getline(&cmdBuffer, &cmdBufferLen, stdin);
		log_cmd("log.txt", cmdBuffer, cmdBufferLen);
		cmdBuffer[cmdBufferLen - 1] = '\0';
		cmd = parse_command(cmdBuffer);
		cmd_path = get_command_path(*cmd);
		if (cmd_path != NULL)
			log_cmd("log_path.txt", cmd_path, _strlen(cmd_path));
		free(cmd->cmd);
		free(cmd->args);
		free(cmd);
		if (!interact_mode)
			break;
	}
	free(cmdBuffer);
	return (0);
}
