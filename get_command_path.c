#include "benny.h"
#include <limits.h>

/**
 * add_pwd_to_paths - if path has extra ':' add cwd
 * @path: path string
 * @pcount: number of paths
 * @env_paths: existing string of path directories
 *
 * Return: new string with cwd added
 */

char **add_pwd_to_paths(char *path, int pcount, char **env_paths)
{
	int i = 0, added = 0, ix;
	char *pwd;
	char **new_paths = NULL;

	pwd = _getenv("PWD");
	if (pwd == NULL)
		return (NULL);
	/* find position to add pwd path */
	if (path[0] == ':')
		ix = 0;
	else if (path[_strlen(path) - 1] == ':')
		ix = pcount - 1;
	/* if pwd is not first or last path, find index */
	else
	{
		for (i = 1, ix = 1; path[i]; i++)
			if (path[i] == ':')
			{
				if (path[i + 1] == ':')
					break;
				ix++;
			}
	}
	new_paths = malloc(sizeof(char *) * (pcount + 1));
	/* add paths to new_path */
	for (i = 0; i < pcount; i++)
	{
		if (i == ix)
		{
			new_paths[i] = _strdup(pwd);
			added = 1;
		}
		else
			new_paths[i] = _strdup(env_paths[i - added]);
	}
	new_paths[i] = NULL;
	free_str_array(env_paths);
	free(pwd);
	free(path);
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
	char *path = NULL, *pwd = NULL;
	char **env_paths = NULL;

	path = _getenv("PATH");
	/* fix to use pwd if PATH is null */
	if (path == NULL)
	{
		pwd = _getenv("PWD");
		env_paths = malloc(sizeof(char *) * 2);
		env_paths[0] = pwd;
		env_paths[1] = NULL;
		return (env_paths);
	}
	for (i = 0; path[i]; i++)
		pcount += path[i] == ':' ? 1 : 0;
	/* if count of ':' in string > len + 2 of env_paths, add PWD */
	env_paths = _strtow(path, ':');
	for (i = 0; env_paths[i]; i++)
		;
	if (i < pcount + 1)
		return (add_pwd_to_paths(path, pcount, env_paths));
	free(path);
	return (env_paths);
}

/**
 * get_command_path - gets path for library functions if exists
 * @cmd: command struct
 *
 * Return: path to command if exists, else null
*/

char *get_command_path(cmd_t *cmd)
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
	if (file_stat == NULL)
		return (NULL);
	env_paths = get_env_paths();
	if (env_paths == NULL)
	{
		free(file_stat);
		return (NULL);
	}
	while (env_paths[i])
	{
		if (i > 0)
			free(cmd_path);
		cmd_path = str_concat(env_paths[i], cmd->cmd, delim);
		found_file = stat(cmd_path, file_stat);
		if (found_file == 0)
			break;
		i++;
	}
	free_str_array(env_paths);
	free(file_stat);
	return (cmd_path);
}
