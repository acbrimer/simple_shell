#include "benny.h"

/**
 * replace_char - replaces find char with replace char in str
 * @str: string to replace chars
 * @find: char to find
 * @replace: char to replace find
 *
 * Return: pointer to string with replaced char
*/
char *replace_char(char *str, char find, char replace)
{
	int i;

	for (i = 0; str[i]; i++)
		if (str[i] == find)
			str[i] = replace;
	return (str);
}
