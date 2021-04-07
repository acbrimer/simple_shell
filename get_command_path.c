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
	char **env_paths;

	/* loop through strings in envp to see if envp[i] is path */
	/* once envp[i] == path, split string on ':' after '=' */
	while (is_path(environ[i]) == 0)
		i++;
	path = _strdup((environ[i] + 5));
	env_paths = _strtow(path, ':');
	free(path);
	return (env_paths);
}

/**
 * get_command_path - gets path for library functions if exists
 * @cmd: command struct
 *
 * Return: path to command if exists, else null
*/
char *get_command_path(cmd_t cmd)
{
	char **env_paths = NULL;
	int i = 0, found_file;
	struct stat file_stat;
	char *cmd_path = NULL;
	char *delim = "/";

	env_paths = get_env_paths();
	while (env_paths[i])
	{
		cmd_path = str_concat(env_paths[i], cmd.cmd, delim);
		found_file = stat(cmd_path, &file_stat);
		if (found_file == 0)
			break;
		i++;
	}
	free_str_array(env_paths);
	if (found_file != 0)
	{
		free(cmd_path);
		return (NULL);
	}
	return (cmd_path);
}
