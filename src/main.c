/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:18:42 by malannys          #+#    #+#             */
/*   Updated: 2019/08/21 17:51:43 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	int		options;
	int		i;

	options = FLAG_RR | FLAG_ONE;
	i = 1; /*opt_parser(ac, av, &options);*/
	if (i == ac)
		read_av(".", options);
	else
	{
		while (i < ac)
			read_av(av[i++], options);
	}
	return (0);
}
