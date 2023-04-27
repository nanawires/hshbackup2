#include "shell.h"

/**
 * is_chain - test if buffer(current char) is a chain delimeter
 * @info: struct for the parameter
 * @buf: buffer to the char
 * @p: current position's address in buf
 *
 * Return: 1 if chain delimeter otherwise, 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';') /* found end of this command */
	{
		buf[k] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * check_chain - continue chaining checks based on last status
 * @info: struct of the parameter
 * @buf: buffer to the char
 * @p: current position's address in buf
 * @len: buf length
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * replace_alias - aliases to be replaced  in the string with tokens
 * @info: struct of the parameter
 *
 * Return: 1 if replaced otherwise, 0
 */
int replace_alias(info_t *info)
{
	int l;
	list_t *node;
	char *p;

	for (l = 0; l < 10; l++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - vars to be replaced in the string with tokens
 * @info: struct of the parameter
 * replace_string - string to be replaced
 *
 * Return: 1 if replaced, 0 if not
 */
int replace_vars(info_t *info)
{
	int l = 0;
	list_t *node;

	for (l = 0; info->argv[l]; l++)
	{
		if (info->argv[l][0] != '$' || !info->argv[l][1])
			continue;

		if (!_strcmp(info->argv[l], "$?"))
		{
			replace_string(&(info->argv[l]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[l], "$$"))
		{
			replace_string(&(info->argv[l]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[l][1], '=');
		if (node)
		{
			replace_string(&(info->argv[l]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[l], _strdup(""));

	}
	return (0);

/**
 * replace_string - string to be replaced
 * @old: old string address
 * @new: new string
 *
 * Return: 1 if replaced, 0 if not
 */
int replace_string(char **old, char *new)
	{
		free(*old);
		*old = new;
		return (1);
	}
}



