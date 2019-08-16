#include "ft_ls.h"

void	push_back(t_node **head, t_node *node)
{
	t_node	*tmp;

	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp = node;
}

void	push_front(t_node **head, t_node *node)
{
	if (*head)
		node->next = *head->next;
	*head = node;
}

/* 
** if malloc fails => return -1, if lstat fails => return 1, else 0
*/
int		create_node(t_node **head, struct dirent *dp, int *options)
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		//error && display error && freeee && return -1
	if (lstat(av, &node->stats) == -1)
		//error && display error && free(node) && return 1
	node->name = strcpy(node->name, dp->d_name);
	node->next = NULL;
	insert_and_sort(head, node, options);
	return (0);
}

void	free_list(t_node** head)
{
	t_node	*prev;
	t_node	*tmp;

	prev = *head;
	while (prev)
	{
		tmp = prev->next;
		free(prev);
		prev = tmp;
	}
	*head = NULL;
}