/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:18:12 by malannys          #+#    #+#             */
/*   Updated: 2019/08/21 19:33:35 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	node->next = *head;
	*head = node;
}

int		add_node(char *path, t_node **head, struct dirent *dp, int *options)
{
	t_node	*node;
	char	*new_path;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		error(MALLOC_FAILURE, NULL);
	if (!(new_path = add_path(path, dp->d_name)))
		error(MALLOC_FAILURE, NULL);
	if (lstat(new_path, &node->stats) == -1)
	{
		error(LSTAT_FAILURE, node->name);
		return (-1);
	}
	ft_strcpy(node->name, dp->d_name);
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
