#include "benny.h"

/**
 * _charcount - counts non-space chars in string
 * @str: input string
 * @delim: delimiter character
 *
 * Return: int count of non-space chars
*/
int _charcount(char *str, char delim)
{
	int i, cc = 0;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] != delim)
			cc++;

	return (cc);
}

/**
 * _wordcount - gets count of words in string sep. by spaces
 * @str: input string
 * @delim: delimiter char
 *
 * Return: int count of words
*/
int _wordcount(char *str, char delim)
{
	int i, wc = 0;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == delim && str[i - 1] != delim)
			wc++;

	return (wc);
}

/**
 * _strtok - returns substring until space delim
 * @str: full string to check
 * @start: starting index in string
 * @delim: delimiter char
 *
 * Return: next string until delim
*/
char *_strtok(char *str, int start, char delim)
{
	int i, l = 0;
	char *s;

	while (str[l + start] != '\0' && str[l + start] != delim)
		l++;
	s = malloc((l + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	for (i = 0; i < l; i++)
		s[i] = str[i + start];
	s[i] = '\0';

	return (s);
}

/**
 * strtow - splits string into array of strings
 * @str: string to split
 * @delim: delimiter char
 * Return: char ** array of strings
*/
char **strtow(char *str, char delim)
{
	int cc = 0, wc = 0, i = 0, r = 0, l, ii;
	char **res;
	char *tmp;

	cc = _charcount(str, delim);
	wc = _wordcount(str, delim);
	if (str == NULL || cc == 0)
		return (NULL);
	res = malloc(sizeof(char *) * cc + wc);
	while (str[i])
	{
		if (str[i] == delim)
			i++;
		else
		{
			l = 0;

			tmp = _strtok(str, i, delim);
			if (tmp == NULL)
				return (NULL);
			while (tmp[l])
				l++;
			res[r] = malloc(sizeof(char) * (l + 1));
			for (ii = 0; ii < l; ii++)
				res[r][ii] = tmp[ii];
			res[r][ii] = '\0';
			free(tmp);
			r++;
			i += l;
		}
	}
	res[r] = NULL;
	if (res == NULL)
		return (NULL);

	return (res);
}
