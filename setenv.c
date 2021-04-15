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
 * @name: name of the env var to remove
 *
 * Return: 0 for success, -1 for fail
*/
int _unsetenv(const char *name)
{
	extern char **environ;
	char **ep, **sp;
	size_t len;

	if (name == NULL || name[0] == '\0' || _strchr((char *)name, '=') != 0)
		return (-1);
	len = _strlen((char *)name);
	for (ep = environ; *ep != NULL; )
		/* check if current ep string == name */
		if (_strncmp(*ep, (char *)name, len) == 0 && (*ep)[len] == '=')
		{
			/* Found entry. Remove and shift all following entries back 1 */
			for (sp = ep; *sp != NULL; sp++)
				*sp = *(sp + 1);
		}
		else
			ep++;
	return (0);
}

/**
 * _setenv - sets a variable in env
 * @name: name of the var to set
 * @value: value to set
 * @overwrite: overwrite existing value = 1
 *
 * Return: 0 for success, -1 for fail
*/
int _setenv(const char *name, const char *value, int overwrite)
{
	char *ev;
	int res = 0, i, ii;

	if (name == NULL || name[0] == '\0' || _strchr((char *)name, '=') != 0 || value == NULL)
		return (-1);
	if (_getenv(name) != NULL && overwrite == 0)
		return (0);
	_unsetenv(name);
	/* malloc for var name + = + value + null byte */
	ev = malloc(sizeof(char) * (_strlen((char *)name) + _strlen((char *)value) + 2));
	if (ev == NULL)
		return (-1);
	for (i = 0, ii = 0; name[i]; i++, ii++)
		ev[ii] = name[i];
	ev[ii] = '=';
	ii++;
	for (i = 0; value[i]; i++, ii++)
		ev[ii] = value[i];
	res = putenv(ev);
	return ((res != 0) ? -1 : 0);
}
