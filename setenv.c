#include "benny.h"


/**
 * *_strncmp - compares first n chars for s1 to s2
 * @s1: first string to be compared
 * @s2: second string to be compared
 * @n: number of chars from s1
 * Return: number of bytes different (0 if identical)
 */
int _strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int x;
	int comp = 0;

	for (x = 0; s1[x] != '\0' && x < n; x++)
	{
		if (s1[x] != s2[x])
		{
			comp = (s1[x] - s2[x]);
			break;
		}
	}
	if (comp != 0)
		return (comp);
	for (x = 0; s2[x] != '\0' && x < n; x++)
	{
		if (s2[x] != s1[x])
		{
			comp = (s2[x] - s1[x]);
			break;
		}
	}
	return (comp);
}


/**
 * _unsetenv - removes env var
 * @n: name of the env var to remove
 *
 * Return: 0 for success, -1 for fail
*/
int _unsetenv(const char *n)
{
	char **new_env, **env_item;
	int nix = -1, i, ii;

	if (n == NULL || n[0] == '\0' || _strchr((char *)n, '=') != 0)
		return (-1);
	/* loop through to find index of env var to remove */
	for (i = 0; environ[i]; i++)
	{
		env_item = _strtow(environ[i], '=');
		/* if text before = on environ[i] matches n, set index and break */
		if (_strcmp((char *)n, env_item[0]) == 0)
			nix = i;
		free_str_array(env_item);
	}
	/* env var doesn't exist so return */
	if (nix == -1)
		return (0);
	/* copy all strings from environ to temp array, free environ, set to temp */
	new_env = malloc(sizeof(char *) * i);
	for (i = 0, ii = 0; environ[ii]; i++, ii++)
	{
		/* copy strings unless we're at the index of var to remove */
		if (i == nix)
		{
			ii++;
			continue;
		}
		new_env[i] = _strdup(environ[ii]);
	}
	new_env[i] = NULL;
	free_str_array(environ);
	environ = new_env;

	return (0);
}

/**
 * _setenv - sets a variable in env
 * @n: name of the var to set
 * @val: value to set
 * @overwrite: overwrite existing value = 1
 *
 * Return: 0 for success, -1 for fail
*/
int _setenv(const char *n, const char *val, int overwrite)
{
	char *ev;
	int res = 0, i, ii;

	if (n == NULL || n[0] == '\0' || _strchr((char *)n, '=') != 0 || val == NULL)
		return (-1);
	if (_getenv(n) != NULL && overwrite == 0)
		return (0);
	_unsetenv(n);
	/* malloc for var name + = + value + null byte */
	ev = malloc(sizeof(char) * (_strlen((char *)n) + _strlen((char *)val) + 2));
	if (ev == NULL)
		return (-1);
	for (i = 0, ii = 0; n[i]; i++, ii++)
		ev[ii] = n[i];
	ev[ii++] = '=';
	for (i = 0; val[i]; i++, ii++)
		ev[ii] = val[i];
	ev[ii] = '\0';
	res = putenv(ev);

	return ((res != 0) ? -1 : 0);
}
