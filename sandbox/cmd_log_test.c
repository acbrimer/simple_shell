#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

/**
 * log_cmd - appends cmd to logfile
 * @logfile: path for logfile to use
 * @cmd: command text
 * @cmd_len: length of command text
*/
int log_cmd(const char *logfile, char *cmd, size_t cmd_len)
{
	int fd;
	ssize_t writelen;
	
	if (logfile == NULL)
		return (-1);
	fd = open(logfile, O_RDWR | O_CREAT | O_APPEND, 0600);
	if (fd < 0)
		return (-1);
	if (cmd)
	{
		writelen = write(fd, cmd, cmd_len);
		if (writelen == -1)
			return (-1);
	}
	close(fd);

	return (1);
}

int main(int argc, char **argv)
{
	while (1)
	{
		size_t cmdBufferLen;
		char *cmdBuffer = NULL;

		cmdBufferLen = getline(&cmdBuffer, &cmdBufferLen, stdin);
		log_cmd("tstoutput.txt", cmdBuffer, cmdBufferLen);
		free(cmdBuffer);
	}

	return (0);
}
