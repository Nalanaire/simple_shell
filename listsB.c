#include "header.h"

/**
 * _list_to_strings - array of strings of the list->str
 * @head: pointer
 * Return: array of strings
 */
char **_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = _malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = _malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * _list_len - length of linked list
 * @b: pointer to first node
 * Return: size of list
 */
size_t _list_len(const list_t *b)
{
	size_t i = 0;

	while (b)
	{
		b = b->next;
		i++;
	}
	return (i);
}

/**
 * _print_list - elements of a list_t the linked list
 * @b: pointer to first node
 *
 * Return: size of list
 */
size_t _print_list(const list_t *b)
{
	size_t i = 0;

	while (b)
	{
		puts(convert_number(b->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		puts(b->str ? b->str : "(nil)");
		puts("\n");
		b = b->next;
		i++;
	}
	return (i);
}

/**
 * _node_starts_with - node whose string starts with prefix
 * @node: pointer
 * @prefix: string
 * @c: character after prefix to match
 * Return: match node or null
 */
list_t *_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _get_node_index - index of a node
 * @head: pointer
 * @node: pointer
 * Return: index of node or -1
 */
ssize_t _get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
