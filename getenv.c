#include "benny.h"

/**
 * _getenv - gets value of environ variable
 * @name: name of variable (e.g. "PATH")
 *
 * Return: pointer to new string with var value or null if not exists
*/
char *_getenv(const char *name)
{
	int i = 0, match = 1;
	char *env_item, *env_val;

	for (i = 0; environ[i]; i++)
	{
		env_item = _strtok(environ[i], 0, '=');
		if (_strcmp(env_item[0], name) == 0)
		{
			env_val = _strdup(env_item[1]);
			free(env_item);
			return (env_val);
		}
		free(env_item);
	}
	return (NULL);
}
