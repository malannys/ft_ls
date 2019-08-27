/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:09:50 by malannys          #+#    #+#             */
/*   Updated: 2019/08/24 20:45:15 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	check_options_a(char *name, int *options)
{
	if (FLAG_A & *options)
		return (1);
	if ((FLAG_AA & *options) && (!ft_strcmp(name, ".") || !ft_strcmp(name, "..")))
		return (0);
	if (!(FLAG_AA & *options) && (name[0] == '.'))
		return (0);
	return (1);
}
void	dir_recursive(t_node **head, int *options)
{
	t_node	*node;

	errno = 0;
	node = *head;
	while (node)
	{
		if (ft_strcmp(".", node->name) && ft_strcmp("..", node->name) \
			&& S_ISDIR(node->stats.st_mode))
		{
			write(1, "\n", 1);
			read_dir(node->path, node->name, options);
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
		if (check_options_a(dp->d_name, options))
			add_node(path, &head, dp->d_name, options);
	if (errno)
		error(READDIR_FAILURE, name);
	if (closedir(dirp) == -1)
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

	options = 0;
	i = opt_parser(ac, av, &options);
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
