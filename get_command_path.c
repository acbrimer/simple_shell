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
 * @envp: environment var
 *
 * Return: array of paths
*/
char **get_env_paths(char **envp)
{
	int i = 0, ii = 0;
	char *p = "PATH";
	char *path;

	/* loop through strings in envp to see if envp[i] is path */
	/* once envp[i] == path, split string on ':' after '=' */
	while (is_path(envp[i]) == 0)
		i++;
	path = envp[i];
	return (strtow((path + 5), ':'));
}
