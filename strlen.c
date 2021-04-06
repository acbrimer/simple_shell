#include "benny.h"

/**
 * _strlen - gets length of string
 * @s: string to get length of
 *
 * Return: length of string
*/
int _strlen(char *s)
{
	int l = 0;

	while (s[l])
		l++;

	return (l);
}
