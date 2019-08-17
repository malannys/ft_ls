/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:18:42 by malannys          #+#    #+#             */
/*   Updated: 2019/08/17 15:19:04 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
