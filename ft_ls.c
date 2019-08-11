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

void	dir_recursive(/*path*/)
{
	//open
	//while readdir
	//	create list
	//sort list
	//display list
	//while (list) {is_dir ? dir_recursive() : continue}
	//clean list
}

void	ft_ls(char *av, int options)
{
	t_node		*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		//error && return
	if (lstat(av, &node->stats) == -1)
	{
		//error && return
	}
	//write path=av
	//if dir => dir_recursive
	//else   => display
}

int		main(int ac, char **av)
{
	int		options;
	int		i;

	options = 0;
	i = opt_parser(ac, av, &options);
	if (i == ac)
		ft_ls(".", options);
	else
	{
		while (i < ac)
		{
			ft_ls(av[i++], options);
		}
	}
	return (0);
}
