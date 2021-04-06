#ifndef _BENNY_H_
#define _BENNY_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

/**
 * struct cmd_s - holds parsed cmd
 * @cmd: command
 * @args: args for command
 * @out_fd: where to write results of command
 *
 * Description: holds all info for a parsed cmd
*/
struct cmd_s
{
	char *cmd;
	char **args;
	int out_fd;
};

typedef struct cmd_s cmd_t;

char **environ;

int log_cmd(const char *logfile, char *cmd, size_t cmd_len);
/* parse_command.c */
cmd_t *parse_command(char *cmd_str);
/* get_command_path.c */
int is_path(char *envp_str);
char **get_env_paths(void);
char *get_command_path(cmd_t cmd);
/* get_command_fn.c */
int (*get_command_fn(cmd_t cmd))(cmd_t);
/* execute_command.c */
int execute_command(cmd_t *cmd);
void handle_command_error(cmd_t cmd);
/* builtin_cd.c */
void _cd(cmd_t cmd);
/* strtok.c */
char **_strtow(char *str, char delim);
char *_strtok(char *str, int start, char delim);
int _charcount(char *str, char delim);
int _wordcount(char *str, char delim);
/* strdup.c */
char *_strdup(char *str);
/* strlen.c */
int _strlen(char *s);
/* str_concat.c */
char *str_concat(char *s1, char *s2);

#endif
