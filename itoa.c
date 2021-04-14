#include "benny.h"

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
