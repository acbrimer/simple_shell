#include "benny.h"

/**
 * str_concat - allocates new memory to concat strings
 * @s1: first string
 * @s2: second string
 * @delim: delimiter to put between concatenated strings
 *
 * Return: concat string
*/
char *str_concat(char *s1, char *s2, char *delim)
{
	int a = 0, b = 0, d = 0, i, l;
	char *n;

	if (s1 != NULL)
		while (s1[a])
			a++;
	if (s2 != NULL)
		while (s2[b])
			b++;
	if (delim != NULL)
		while (delim[d])
			d++;
	l = a + b + d;
	n = (char *)malloc(sizeof(char) * l + 1);
	if (n == NULL)
		return (NULL);
	for (i = 0; i < a; i++)
		n[i] = s1[i];
	if (delim != NULL)
		for (; i < (a + d); i++)
			n[i] = delim[i - a];
	for (; i < l; i++)
		n[i] = s2[i - a - d];
	n[l] = '\0';
	return (n);
}
