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
	char *n = NULL;

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
	n = malloc(sizeof(char) * l + 1);
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

/**
 * _strchr - finds first char in str
 * @s: string to search
 * @c: char to search for
 *
 * Return: 1 for has char, else 0
 */
int _strchr(char *s, char c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (0);

	return (0);
}

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
	if (comp != 0)
		return (comp);
	for (x = 0; s2[x] != '\0'; x++)
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
	n = malloc(sizeof(char) * (l + 1));
	if (n == NULL)
		return (NULL);
	for (i = 0; i < l; i++)
		n[i] = str[i];
	n[i] = '\0';

	return (n);
}

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
