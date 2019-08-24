/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:09:50 by malannys          #+#    #+#             */
/*   Updated: 2019/08/24 17:48:32 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	dir_recursive(t_node **head, int *options)
{
	t_node	*node;

	errno = 0;
	node = *head;
	while (node)
	{
		if (ft_strcmp(".", node->name) && ft_strcmp("..", node->name) \
			&& S_ISDIR(node->stats.st_mode))
			read_dir(node->path, node->name, options);
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
		add_node(path, &head, dp->d_name, options);
	if (errno)
		error(READDIR_FAILURE, name);
	if(closedir(dirp) == -1)
		error(CLOSEDIR_FAILURE, name);
	print(path, head, options);
	if (FLAG_RR & *options)
		dir_recursive(&head, options);
	free_list(&head);
}

int		main(int ac, char **av)
{
	int		options;
	int		i;
	t_node	*head;

	options = FLAG_ONE | FLAG_U | FLAG_T;
	i = 1; /*opt_parser(ac, av, &options);*/
	if (i == ac)
		read_dir(".", ".", &options);
	else
		while (i < ac)
		{
			errno = 0;
			head = NULL;
			add_node(NULL, &head, av[i], &options);
			if (head && S_ISDIR(head->stats.st_mode))
				read_dir(av[i], av[i], &options);
			else
				print(av[i], head, &options);
			free_list(&head);
			i++;
		}
	return (0);
}
