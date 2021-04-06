#include "benny.h"

/**
 * _strdup - copies string using malloc
 * @str: string to copy
 *
 * Return: char * pointer to copied string
*/
char *_strdup(char *str)
{
	int l = 0, i;
	char *n = NULL;

	if (str == NULL)
		return (NULL);
	while (str[l])
		l++;
	n = (char *)malloc(l + 1);
	if (n == NULL)
		return (NULL);
	for (i = 0; i < l; i++)
		n[i] = str[i];
	n[l] = '\0';

	return (n);
}
