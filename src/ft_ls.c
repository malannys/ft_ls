/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:09:50 by malannys          #+#    #+#             */
/*   Updated: 2019/08/21 19:28:49 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*add_path(char *path, char *name)
{
	size_t	len1;
	size_t	len2;
	char	*new_path;

	errno = 0;
	len1 = ft_strlen(path);
	len2 = ft_strlen(name);
	if (!(new_path = (char *)malloc(len1 + len2 + 2)))
		error(MALLOC_FAILURE, NULL);
	ft_memcpy(new_path, path, len1);
	*(new_path + len1) = '/';
	ft_memcpy(new_path + len1 + 1, name, len2);
	*(new_path + len1 + len2 + 1) = '\0';
	return (new_path);
}

void	dir_recursive(char *path, t_node **head, int *options)
{
	t_node	*node;
	char	*new_path;

	errno = 0;
	node = *head;
	while (node)
	{
		if (ft_strcmp(".", node->name) && ft_strcmp("..", node->name) \
			&& S_ISDIR(node->stats.st_mode))
		{
			if (!(new_path = add_path(path, node->name)))
				error(MALLOC_FAILURE, NULL);
			read_dir(new_path, node->name, options);
			free(new_path);
		}
		node = node->next;
	}
}

void	read_dir(char *path, char *name, int *options)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_node			*head;

	head = NULL;
	errno = 0;
	if (!(dirp = opendir(path)))
	{
		error(OPENDIR_FAILURE, name);
		return ;
	}
	while ((dp = readdir(dirp)))
		if (add_node(path, &head, dp, options) == -1)
			continue;
	if (errno)
		error(READDIR_FAILURE, name);
	if(closedir(dirp) == -1)
		error(CLOSEDIR_FAILURE, name);
	print(path, head, options);
	if (FLAG_RR & *options)
		dir_recursive(path, &head, options);
	free_list(&head);
}

/*
** if av - file => print stat
** if av - dir => read_dir()
*/
void	read_av(char *av, int options)
{
	t_node		*node;

	errno = 0;
	if (!(node = (t_node *)malloc(sizeof(t_node))))
		error(MALLOC_FAILURE, NULL);
	if (lstat(av, &node->stats) == -1)
	{
		error(LSTAT_FAILURE, av);
		return ;
	}
	strcpy(node->name, av);
	node->next = NULL;
	if (S_ISDIR(node->stats.st_mode))
		read_dir(av, av, &options);
	else
		print(av, node, &options);
	free_list(&node);
}
