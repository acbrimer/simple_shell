#include "benny.h"

/**
 * str_concat - allocates new memory to concat strings
 * @s1: first string
 * @s2: second string
 *
 * Return: concat string
*/
char *str_concat(char *s1, char *s2)
{
	int a = 0, b = 0, i, l;
	char *n;

	if (s1 != NULL)
		while (s1[a])
			a++;
	if (s2 != NULL)
		while (s2[b])
			b++;
	l = a + b;
	n = (char *)malloc(sizeof(char) * l + 1);
	if (n == NULL)
		return (NULL);
	for (i = 0; i < a; i++)
		n[i] = s1[i];
	for (; i < l; i++)
		n[i] = s2[i - a];
	n[l] = '\0';

	return (n);
}
