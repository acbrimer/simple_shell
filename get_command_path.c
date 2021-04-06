#include "benny.h"

/**
 * is_path - checks if environ var is PATH
 * @s: string environment var
 *
 * Return: 1 for path, else 0
*/
int is_path(char *s)
{
	int i = 0;
	char *p = "PATH";

	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		if (s[i] != p[i])
			break;
		i++;
	}

	return (0);
}

/**
 * get_env_paths - returns array of paths from current env
 *
 * Return: array of paths
*/
char **get_env_paths(void)
{
	int i = 0;
	char *p = "PATH";
	char *path;

	/* loop through strings in envp to see if envp[i] is path */
	/* once envp[i] == path, split string on ':' after '=' */
	while (is_path(environ[i]) == 0)
		i++;
	path = environ[i];
	return (_strtow((path + 5), ':'));
}

/**
 * get_command_path - gets path for library functions if exists
 * @cmd: command struct
 *
 * Return: path to command if exists, else null
*/
char *get_command_path(cmd_t cmd)
{
	char **env_paths;
	int i = 0, found_file;
	char *full_path;
	struct stat file_stat;

	env_paths = get_env_paths();
	while (env_paths[i])
	{
		full_path = _strdup(str_concat(str_concat(env_paths[i],"/"), cmd.cmd));
		found_file = stat(full_path, &file_stat);
		if (found_file == 0)
			return (full_path);
		i++;
	}

	return (NULL);
}

