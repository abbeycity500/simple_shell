#include "shell.h"
#include <stdio.h>

/**
 * _reverse - reverses the content of a string
 * @str: string to reverse
 * @n: lengeth of string
 * Return: reversed string
 */

char *_reverse(char *str, int n)
{
	char *begin = str;
	char *end;
	char hold;

	end = str + n - 1;
	for (; begin < end; begin++, end--)
	{
		hold = *end;
		*end = *begin;
		*begin = hold;
	}
	return (str);
}

/**
 * _itoa - converts an integer base 10 to a string
 * @num: integer to convert
 * Return: integer in string format
 */

char *_itoa(int num)
{
	int i = 0, neg = 0, cnum = num, len, remainder = 0;
	char *str;

	for (len = 0; cnum; cnum /= 10)
		;

	/* check if num is 0 */
	if (num == 0)
	{
		str = do_mem(2 * sizeof(char), NULL);
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}
	/* check if negative number */
	if (num < 0)
	{
		neg = 1;
		num = -num;
		len++;
	}
	/* malloc for size of string */
	str = do_mem((len + 1) * sizeof(char), NULL);
	/* handle individual numbers */
	while (num != 0)
	{
		remainder = num % 10;
		str[i++] = remainder + '0';
		num = num / 10;
	}
	/* Add negative sign if negatice */
	if (neg)
		str[i++] = '-';
	/* add null bite */
	str[i] = '\0';
	/* reverse string */
	_reverse(str, i);

	return (str);
}

/**
 * _memset - memset function
 * @s: start point of string to change
 * @b: value that will replace
 * @n: number of bytes to change
 * Return: changed pointer
 */

char *_memset(char *s, char b, int n)
{
	char *p = s;

	for (; n != 0; p++, n--)
		*p = b;
	return (s);
}
