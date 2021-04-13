#ifndef _BENNY_H_
#define _BENNY_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

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

extern char **environ;

int log_cmd(const char *logfile, char *cmd, size_t cmd_len);
/* parse_command.c */
cmd_t *parse_command(char *cmd_str);
/* get_command_path.c */
char **get_env_paths(void);
char *get_command_path(cmd_t *cmd, char *argv);
/* get_command_fn.c */
int (*get_command_fn(cmd_t cmd))(cmd_t);
/* execute_command.c */
int execute_command(cmd_t *cmd, char *argv, char *cmdBuffer);
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
char *str_concat(char *s1, char *s2, char *delim);
/* free_mem_fns.c */
char **free_str_array(char **arr);
void free_cmd_t(cmd_t *cmd);
/* strcmp.c */
int _strcmp(char *s1, char *s2);
/* strchr.c */
int _strchr(char *s, char c);
/* builtin.c */
int builtin(cmd_t *cmd, char *cmdBuffer);
void exitFunction(cmd_t *cmd, char *cmdBuffer);
void printEnv(void);
/* getenv.c */
char *_getenv(const char *name);
void _setenv(cmd_t *cmd);
/* error.c */
void errorNotFound(char *argv, char *command);
/* replace_char.c */
char *replace_char(char *str, char find, char replace);
#endif
