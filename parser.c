#include "shell.h"

/**
 * is_cmd - finds out if a file is an exe command
 * @info: struct to the info
 * @path: file path
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat struc;

	(void)info;
	if (!path || stat(path, &struc))
		return (0);

	if (struc.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: string to the PATH
 * @start: start of index
 * @stop: stop of index
 *
 * Return: new buffer pointer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, c = 0;

	for (c = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[c++] = pathstr[a];
	buf[c] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the string of PATH
 * @info: struct of the info
 * @pathstr: the string to the PATH
 * @cmd: command to find
 *
 * Return: path of command if found or NULL if otherwise
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, cposition = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, cposition, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			cposition = a;
		}
		a++;
	}
	return (NULL);
}
