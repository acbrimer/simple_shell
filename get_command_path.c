#include "benny.h"
#include <limits.h>

/**
 * add_pwd_to_paths - if path has extra ':' add cwd
 * @env_paths: existing string of path directories
 * @total_paths: number of existing directories in path
 *
 * Return: new string with cwd added
 */

char **add_pwd_to_paths(char **env_paths, int total_paths)
{
	int i = 0;
	char *pwd;
	char **new_paths;

	pwd = malloc((size_t)PATH_MAX);
	getcwd(pwd, (size_t)PATH_MAX);
	new_paths = malloc(sizeof(char **) * (total_paths + 2));
	for (i = 0; i < total_paths; i++)
		new_paths[i] = _strdup(env_paths[i]);
	new_paths[i] = _strdup(pwd);
	new_paths[i + 1] = NULL;
	free_str_array(env_paths);

	return (new_paths);
}

/**
 * get_env_paths - returns array of paths from current env
 *
 * Return: array of paths
*/

char **get_env_paths(void)
{
	int i = 0, match = 1, pcount = 0;
	char *path;
	char **env_paths, *env_var;

	/* loop through strings in envp to see if envp[i] is path */
	/* once envp[i] == path, split string on ':' after '=' */
	for (i = 0; environ[i]; i++)
	{
		env_var = _strtok(environ[i], 0, '=');
		match = _strcmp(env_var, "PATH");
		free(env_var);
		if (match == 0)
			break;
	}
	path = environ[i] + 5;
	for (i = 0; path[i]; i++)
		pcount += path[i] == ':' ? 1 : 0;
	/* count ':' in path string */
	/* if count of ':' in string > len + 2 of env_paths, add PWD */
	env_paths = _strtow(path, ':');
	for (i = 0; env_paths[i]; i++)
		;
	if (i < pcount + 1)
		return (add_pwd_to_paths(env_paths, i));
	return (env_paths);
}

/**
 * get_command_path - gets path for library functions if exists
 * @cmd: command struct
 *
 * Return: path to command if exists, else null
*/
char *get_command_path(cmd_t cmd, char *argv)
{
	char **env_paths = NULL;
	int i = 0, found_file;
	struct stat *file_stat;
	char *cmd_path = NULL;
	char *delim = "/";

	/* if cmd.cmd starts with i/, use as path w/out concat PATH */
	if (cmd.cmd && _strchr(cmd.cmd, '/') != 0)
		return (_strdup(cmd.cmd));
	file_stat = malloc(sizeof(struct stat));
	env_paths = get_env_paths();
	while (env_paths[i])
	{
		cmd_path = str_concat(env_paths[i], cmd.cmd, delim);
		found_file = stat(cmd_path, file_stat);
		if (found_file == 0)
			break;
		free(cmd_path);
		i++;
	}
	free(file_stat);
	if (found_file != 0)
	{
		errorNotFound(argv, cmd.cmd);
		return (NULL);
	}
	return (cmd_path);
}
