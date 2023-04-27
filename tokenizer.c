#include "shell.h"

/**
 * * **strtow - divides strings to words; duplicate delimiters are ignored
 * @str: string of the input
 * @d: string of the delimiter
 * Return: an array pointer of strings or NULL if otherwise
 */

char **strtow(char *str, char *d)
{
	int a, b, c, e, digits = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			digits++;

	if (digits == 0)
		return (NULL);
	s = malloc((1 + digits) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < digits; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - divides strings into words
 * @str: string of the input
 * @d: delimiter
 * Return: array pointer of strings or NULL if otherwise
 */
char **strtow2(char *str, char d)
{
	int a, b, c, e, digits = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				(str[a] != d && !str[a + 1]) || str[a + 1] == d)
			digits++;
	if (digits == 0)
		return (NULL);
	s = malloc((1 + digits) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < digits; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}

