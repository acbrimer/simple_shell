#include "benny.h"
#include <limits.h>

/**
 * add_pwd_to_paths - if path has extra ':' add cwd
 * @env_paths: existing string of path directories
 * @total_paths: number of existing directories in path
 *
 * Return: new string with cwd added
 */
char **add_pwd_to_paths(char **env_paths)
{
	int i = 0;
	char *pwd;
	char **new_paths = NULL;

	pwd = _getenv("PWD");
	for (i = 0; env_paths[i]; i++)
		new_paths[i] = _strdup(env_paths[i]);
	new_paths[i] = _strdup(pwd);
	new_paths[i + 1] = NULL;
	free_str_array(env_paths);
	free(pwd);

	return (new_paths);
}

/**
 * get_env_paths - returns array of paths from current env
 *
 * Return: array of paths
*/
char **get_env_paths(void)
{
	int i = 0, pcount = 0;
	char *path;
	char **env_paths = NULL;

	path = _getenv("PATH");
	for (i = 0; path[i]; i++)
		pcount += path[i] == ':' ? 1 : 0;
	/* if count of ':' in string > len + 2 of env_paths, add PWD */
	env_paths = _strtow(path, ':');
	free(path);
	for (i = 0; env_paths[i]; i++)
		;
	if (i < pcount + 1)
		return (add_pwd_to_paths(env_paths));
	return (env_paths);
}

/**
 * get_command_path - gets path for library functions if exists
 * @cmd: command struct
 * @argv: name of program
 *
 * Return: path to command if exists, else null
*/
char *get_command_path(cmd_t *cmd, char *argv)
{
	char **env_paths = NULL;
	int i = 0, match = 1, found_file;
	struct stat *file_stat;
	char *cmd_path = NULL;
	char *delim = "/";

	/* if cmd.cmd starts with i/, use as path w/out concat PATH */
	match = _strchr(cmd->cmd, '/');
	if (match != 0)
	{
		cmd_path = _strdup(cmd->cmd);
		return (cmd_path);
	}
	file_stat = malloc(sizeof(struct stat));
	env_paths = get_env_paths();
	while (env_paths[i])
	{
		cmd_path = str_concat(env_paths[i], cmd->cmd, delim);
		found_file = stat(cmd_path, file_stat);
		if (found_file == 0)
			break;
		free(cmd_path);
		i++;
	}
	free_str_array(env_paths);
	free(file_stat);
	if (found_file != 0)
	{
		errorNotFound(argv, cmd->cmd);
		return (NULL);
	}
	return (cmd_path);
}
