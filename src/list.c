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
	while (head && *head)
		head = &(*head)->next;
	*head = node;
}

void	push_front(t_node **head, t_node *node)
{
	node->next = *head;
	*head = node;
}

void	add_node(char *path, t_node **head, char *name, int *options)
{
	t_node	*node;

	errno = 0;
	if (!(node = (t_node *)malloc(sizeof(t_node))))
		error(MALLOC_FAILURE, NULL);
	if (!(node->path = add_path(path, name)))
		error(MALLOC_FAILURE, NULL);
	if (lstat(node->path, &node->stats) == -1)
	{
		error(LSTAT_FAILURE, name);
		free(node->path);
		free(node);
		return ;
	}
	ft_strcpy(node->name, name);
	node->next = NULL;
	insert_and_sort(head, node, options);
}

void	free_list(t_node **head)
{
	t_node	*tmp;
	t_node	*prev;

	prev = *head;
	while (tmp)
	{
		tmp = prev->next;
		free(prev->path);
		free(prev);
		prev = tmp;
	}
	*head = NULL;
}

char	*add_path(char *path, char *name)
{
	size_t	len1;
	size_t	len2;
	char	*new_path;

	errno = 0;
	if (!(path && name) || !ft_strcmp(path, "/"))
		return (ft_strjoin(path, name));
	len1 = ft_strlen(path);
	len2 = ft_strlen(name);
	if ((new_path = (char *)malloc(len1 + len2 + 2)))
	{
		ft_memcpy(new_path, path, len1);
		*(new_path + len1) = '/';
		ft_memcpy(new_path + len1 + 1, name, len2);
		*(new_path + len1 + len2 + 1) = '\0';
	}
	return (new_path);
}
