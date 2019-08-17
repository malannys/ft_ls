/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:09:50 by malannys          #+#    #+#             */
/*   Updated: 2019/08/11 19:09:52 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

char	*add_path(char *path, char *name)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*new_path;

	i = 0;
	errno = 0;
	len1 = ft_strlen(path);
	len2 = ft_strlen(name);
	if (!(new_path = (char *)malloc(len1 + len2 + 2)))
		// error && display error && return -1
	while (i < len1)
		*(new_path + i) = *(path + i++);
	*(new_path + i) = "/";
	i = 0;
	while (i < len2)
		*(new_path + i + len1 + 1) = *(name + i++);
	*(new_path + i + len1 + 1) = "\0";
	return (new_path);
}

int		dir_recursive(char *path, t_node **head, int *options)
{
	t_node	*node;
	char	*new_path;

	node = *head;
	while (node)
	{
		if (ft_strcmp(".", node->name) && ft_strcmp("..", node->name) \\
			&& S_ISDIR(node->stats.st_mode))
		{
			if (!(new_path = add_path(path, node->name)))
				// error && display error && free && return -1
			if (read_dir(new_path, options) == -1) //concat path, free???
				// error && display error? && free && return -1
		}
		node = node->next;
	}
}

int		read_dir(char *path, int *options)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_node			*head;

	head = NULL;
	errno = 0;
	if (!(dirp = opendir(path)))
		error();
		// error && display error && return -1
	while ((dp = readdir(dirp)))
		if (create_node(&head, dp, options) == -1) // sorting and freeing (???) if fails are also here
			// (EXIT????) free **head and return -1
	//if (errno)
	//
	closedir(dirp);
	print(path, head, options);
	if (FLAG_RR & *options)
		if ((dir_recursive(path, head, options)) == -1)
			// error && return -1
	free_list(&head);
	return (0);
}

int		ft_ls(char *av, int options)
{
	t_node		*node;

	errno = 0;
	if (!(node = (t_node *)malloc(sizeof(t_node))))
		error();
		//error && display error && EXIT
	if (lstat(av, &node->stats) == -1)
		error();
		//error && display error && return -1
	node->name = strcpy(node->name, av);
	node->next = NULL;
	if (S_ISDIR(node->stats.st_mode))
		if (read_dir(av, &options) == -1) //to exit or not to exit?
			//return -1
	else
		display(av, node, &options);
	free_list(&node);
	return (0);
}
