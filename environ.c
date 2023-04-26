#include "header.h"

/**
 * _byenv - current environment
 * @info: potential arguments. to maintain
 *constant function prototype.
 *Return: Always 0
 */
int _byenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - value of an environ variable
 *@info: potential arguments. to maintain
 *@name: var name
 *Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _bysetenv - environment variable,
 *or modify an existing one
 *@info: potential arguments. to maintain
 *constant function prototype.
 *Return: Always 0
 */
int _bysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _byunsetenv - environment variable
 *@info: potential arguments. to maintain
 *constant function prototype.
 *Return: Always 0
 */
int _byunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * expand_env_list - expand env linked list
 *@info: potential arguments. to maintain
 *constant function prototype.
 *Return: Always 0
 */
int expand_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
