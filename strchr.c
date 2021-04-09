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
