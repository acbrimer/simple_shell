

int main(int argc, char **argv)
{
	int run_shell = 1;
	int interact_mode = isatty(STDIN_FILENO);
	size_t cmdBufferLen;
	char *cmdBuffer = NULL;

	while (1)
	{
		if (interact_mode)
			printf("BENNY$ ");
		cmdBufferLen = getline(&cmdBuffer, &cmdBufferLen, stdin);
		log_cmd("log.txt", cmdBuffer, cmdBufferLen);
		if (!interact_mode)
			break;
	}
	free(cmdBuffer);
	return (0);
}
