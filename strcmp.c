#include "benny.h"

/**
 * *_strcmp - compares 2 strings
 * @s1: first string to be compared
 * @s2: second string to be compared
 * Return: number of bytes different (0 if identical)
 */

int _strcmp(char *s1, char *s2)
{
	int x;
	int comp = 0;

	for (x = 0; s1[x] != '\0'; x++)
	{
		if (s1[x] != s2[x])
		{
			comp = (s1[x] - s2[x]);
			break;
		}
	}
	return (comp);
}
