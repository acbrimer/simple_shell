#include "benny.h"
#include <limits.h>
/**
 * _itoa - converts int to string
 * @n: int to convert
 *
 * Return: pointer to malloced string with digits from n
*/
char *_itoa(int n)
{
	char temp[20] = "00000000000000000000";
	char *res;
	int i = 0, ii = 0, c = n, d;

	if (n < 0)
		temp[ii++] = '-';
	for (i = 1000000000; i >= 1; i /= 10)
	{
		if ((n >= 0 && n >= i) || (n < 0 && n <= -i))
		{
			d = c / i;
			temp[ii++] = (d < 0 ? -d : d) + '0';
			c = d == 0 ? c : c - (d * i);
		}
	}
	/*malloc now that we know how many digits */
	res = malloc(sizeof(char) * (ii + 1));
	/*copy contents of temp into res */
	for (i = 0; i < ii; i++)
		res[i] = temp[i];
	res[i] = '\0';
	return (res);
}

/**
 * _atoi - returns signed int from string
 * @s: string w/ int
 *
 * Return: int found in string
*/
int _atoi(char *s)
{
	unsigned int i = 0, start, end;
	int started = 0, finished = 0, num = 0, nth = 1, sign = -1;

	while (finished == 0)
	{
		char c = *(s + i);

		if (c == '-')
			sign = sign == 1 ? -1 : 1;
		if (c >= '0' && c <= '9' && started == 0)
		{
			start = i;
			started = 1;
		}
		if (c == '\0' || ((c < '0' || c > '9') && started == 1))
		{
			end = i - 1;
			finished = 1;
		}
		i++;
	}
	if (started == 0)
		return (0);
	for (i = end; i >= start; i--)
	{
		int d = *(s + i) - 48;

		if (sign == -1 && ((d - 48) * nth) > INT_MAX + num)
			return (num * -1);
		else if (sign == 1 && ((d * nth) * -1) < INT_MIN - num)
			return (num);
		num -= (*(s + i) - 48) * nth;
		nth *= 10;
		if (i == 0)
			break;
	}

	return (num * sign);
}
