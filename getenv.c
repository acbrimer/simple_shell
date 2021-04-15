#include "benny.h"

/**
 * _getenv - gets value of environ variable
 * @name: name of variable (e.g. "PATH")
 *
 * Return: pointer to new string with var value or null if not exists
*/
char *_getenv(const char *name)
{
	int i = 0;
	char **env_item, *env_val, *env_var = (char *)name;

	for (i = 0; environ[i]; i++)
	{
		env_item = _strtow(environ[i], '=');
		if (_strcmp(env_var, env_item[0]) == 0)
		{
			env_val = _strdup(env_item[1] == NULL ? "" : env_item[1]);
			free_str_array(env_item);
			return (env_val);
		}
		free_str_array(env_item);
	}
	return (NULL);
}
