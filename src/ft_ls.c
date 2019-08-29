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
			read_dir(node->path, node, options);
		}
		node = node->next;
	}
}

void	read_dir(char *path, t_node *node, int *options)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_node			*head;

	head = NULL;
	errno = 0;
	if (!(dirp = opendir(node->path)))
	{
		error(OPENDIR_FAILURE, node->name);
		return ;
	}
	while ((dp = readdir(dirp)))
		if (check_options_a(dp->d_name, options))
			insert_and_sort(&head, add_node(node->path, dp->d_name, options, 0), options);
	if (errno)
		error(READDIR_FAILURE, node->name);
	if (closedir(dirp) == -1)
		error(CLOSEDIR_FAILURE, node->name);
	print(path, head, options);
	if (FLAG_RR & *options)
		dir_recursive(&head, options);
	free_list(&head);
}

void	read_args(int ac, char **av, int *options, int arg)
{
	int			i;
	t_node		*tmp;
	t_node		*head_file;
	t_node		*head_dir;

	i = arg - 1;
	head_dir = NULL;
	head_file = NULL;
	while (++i < ac)
	{
		tmp = add_node(".", av[i], options, 1);
		if (tmp && S_ISDIR(tmp->stats.st_mode))
			insert_and_sort(&head_dir, tmp, options);
		else if (tmp)
			insert_and_sort(&head_file, tmp, options);
	}
	print(NULL, head_file, options);
	tmp = head_dir;
	while (tmp)
	{
		read_dir(tmp->name, tmp, options);
		tmp = tmp->next;
	}
	free(head_dir);
	free(head_file);
}

int		main(int ac, char **av)
{
	int		options;
	int		i;
	t_node	tmp;

	options = 0;
	i = opt_parser(ac, av, &options);
	if (i == ac)
	{
		tmp.path = ".";
		ft_strcpy(tmp.name, ".");
		read_dir(NULL, &tmp, &options);
	}
	else
		read_args(ac, av, &options, i);
	return (0);
}
