#include "shell.h"

/**
 * get_history_file - access history files
 * @info: struct of the parameter
 *
 * Return: history file contained in the specified string
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates new file or appends it when neccesary
 * @info: struct parameter
 *
 * Return: 1 on success, -1 otherwise
 */
int write_history(info_t *info)
{
	ssize_t resp;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	resp = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (resp == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, resp);
		_putfd('\n', resp);
	}
	_putfd(BUF_FLUSH, resp);
	close(resp);
	return (1);
}

/**
 * read_history - file is read from history
 * @info: struct for the parameter
 *
 * Return: histcount on success, 0 on failure
 */
int read_history(info_t *info)
{
	int k, final = 0, linechkno = 0;
	ssize_t resp, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	resp = open(filename, O_RDONLY);
	free(filename);
	if (resp == -1)
		return (0);
	if (!fstat(resp, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(resp, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(resp);
	for (k = 0; k < fsize; k++)
		if (buf[k] == '\n')
		{
			buf[k] = 0;
			build_history_list(info, buf + final, linechkno++);
			final = k + 1;
		}
	if (final != k)
		build_history_list(info, buf + final, linechkno++);
	free(buf);
	info->histcount = linechkno;



