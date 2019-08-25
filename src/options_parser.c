/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 20:32:16 by abartole          #+#    #+#             */
/*   Updated: 2019/08/25 20:19:10 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	error_managment(char *str, int error)
{
	char	*s;

	s = "usage: ft_ls [-1AaBCcdeFfGgilmnopqRrSTtuUvw@H] [file ...]";
	if (error == 1)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(*str, 2);
		ft_putchar_fd('\n', 2);
		ft_putendl_fd(s, 2);
	}
	return (0);
}

static int	get_index(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

static int	get_options(char *str, int *options)
{
	int	n;

	while (*(++str))
	{
		if ((n = get_index("1AaBCcdeFfGgilmnopqRrSTtuUvw@iH", *str)) == -1)
			error_managment(str, 1);
		*options |= (1 << n);
		check_options(str, options);
	}
	return (1);
}

int			opt_parser(int ac, char **av, int *options)
{
	int i;

	i = 0;
	while (++i < ac && av[i][0] == '-' && av[i][1])
	{
		if (av[i][1] == '-' && av[i][2])
			return (i + 1);
		if (!get_options(av[i], options))
			return (-1);
	}
	check_all_flags(options);
	return (i);
}
