#ifndef _BENNY_H_
#define _BENNY_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

/**
 * struct cmd_s - holds parsed cmd
 * @cmd: command
 * @args: args for command
 *
 * Description: holds all info for a parsed cmd
*/

typedef struct cmd_s
{
	char *cmd;
	char **args;
} cmd_t;

extern char **environ;
extern int errno;

/* main.c */
void check_linelen(char *exename, char *cmdBuffer, int mode, int linelen);
void sigint_handler(int sig);
void main_cleanup(void) __attribute__ ((destructor));
void set_environ(void);
/* parse_command.c */
cmd_t *parse_command(char *cmd_str);
char *replace_char(char *str, char find, char replace);
/* get_command_path.c */
char **get_env_paths(void);
char *get_command_path(cmd_t *cmd);
char **add_pwd_to_paths(char *path, int pcount, char **env_paths);
/* execute_command.c */
int execute_command(cmd_t *cmd, char *cmdBuffer, int linec, char *exename);
int check_file_exists(char *path);
void free_cmd_vars(cmd_t *cmd, char *cmd_path, char *cmdBuffer);
int f_error(char *err, int eno, cmd_t *cmd, int linec, char *exe, char *path);
/* setenv.c */
int _unsetenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _strncmp(char *s1, char *s2, unsigned int n);
/* getenv.c */
char *_getenv(const char *name);
/* strtok.c */
char **_strtow(char *str, char delim);
char *_strtok(char *str, int start, char delim);
int _charcount(char *str, char delim);
int _wordcount(char *str, char delim);
/* string.c */
char *_strdup(char *str);
int _strlen(char *s);
char *str_concat(char *s1, char *s2, char *delim);
int _strcmp(char *s1, char *s2);
int _strchr(char *s, char c);
/* free_mem_fns.c */
char **free_str_array(char **arr);
void free_cmd_t(cmd_t *cmd);
/* builtin.c */
int builtin(cmd_t *cmd, char *cmdBuffer);
void cdFunction(cmd_t *cmd, char *cmdBuffer);
void exitFunction(cmd_t *cmd, char *cmdBuffer);
void printEnv(void);
/* getenv.c */
char *_getenv(const char *name);
/* itoa.c */
char *_itoa(int n);
int _atoi(char *s);

#endif
