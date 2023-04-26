#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: final location
 * @src: origin
 *
 * Return: pointer to final location
 */
char *_strcpy(char *dest, char *src)
{
	int k = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[k])
	{
		dest[k] = src[k];
		k++;
	}
	dest[k] = 0;
	return (dest);
}

/**
 *  _strdup - duplicates a string
 *  @str: string to be duplicated
 *
 *  Return: pointer to string (duplicated)
 */
char *_strdup(const char *str)
{
	int dimsn = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		dimsn++;
	ret = malloc(sizeof(char) * (dimsn + 1));
	if (!ret)
		return (NULL);
	for (dimsn++; dimsn--;)
		ret[dimsn] = *--str;
	return (ret);
}

/**
 * _puts - displays an input string
 * @str: the string yet to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int k = 0;

	if (!str)
		return;
	while (str[k] != '\0')
	{
		_putchar(str[k]);
		k++;
	}
}

/**
 * _putchar - char c is written to stdout
 * @c: char yet to be printed
 *
 * Return: 1 on success and -1 otherwise
 */
int _putchar(char c)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}
