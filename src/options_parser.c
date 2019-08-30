/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 20:32:16 by abartole          #+#    #+#             */
/*   Updated: 2019/08/30 22:18:55 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	error_managment(char *str, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(*str, 2);
		ft_putchar_fd('\n', 2);
		ft_putendl_fd("usage: ft_ls [-1AaBCcdeFfGgilmnopqRrSTtuUvw@] [file ...]", 2);
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

static void	check_options1(char *str, int *options)
{
	if (*str == 'c')
		*options &= ~(FLAG_U);
	else if (*str == 'B')
	{
		*options &= ~(FLAG_W);
		*options &= ~(FLAG_Q);
	}
	else if (*str == 'w')
	{
		*options &= ~(FLAG_Q);
		*options &= ~(FLAG_BB);
	}
	else if (*str == 'q')
	{
		*options &= ~(FLAG_BB);
		*options &= ~(FLAG_W);
	}
	else if (*str == 'n')
		*options &= ~(FLAG_L);
	else if (*str == 'u')
		*options &= ~(FLAG_C);
}	

static void	check_options(char *str, int *options)
{
	if (*str == 'l')
	{
		*options &= ~(FLAG_ONE);
		*options &= ~(FLAG_CC);
		*options &= ~(FLAG_M);
		*options &= ~(FLAG_HH);
	}
	else if (*str == 'C')
	{
		*options &= ~(FLAG_ONE);
		*options &= ~(FLAG_L);
		*options &= ~(FLAG_M);
	}
	else if (*str == '1')
	{
		*options &= ~(FLAG_L);
		*options &= ~(FLAG_CC);
		*options &= ~(FLAG_M);
		*options &= ~(FLAG_N);
	}
	else if (*str == 'm')
	{
		*options &= ~(FLAG_L);
		*options &= ~(FLAG_CC);
		*options &= ~(FLAG_ONE);
	}	
	check_options1(str, options);
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

static void	check_all_flags1(int *options)
{
	if (*options & FLAG_SS)
	{
		*options &= ~(FLAG_U);
		*options &= ~(FLAG_UU);
		*options &= ~(FLAG_C);
	}
	if (*options & FLAG_D)
		*options &= ~(FLAG_HH);
	if (*options & FLAG_FF)
		*options &= ~(FLAG_HH);
}

static void	check_all_flags(int *options)
{
	*options |= FLAG_HH;
	if (!(*options & FLAG_L))
		*options &= ~(FLAG_TT);
	if (!((*options & FLAG_L) || (*options & FLAG_T)))
		*options &= ~(FLAG_C);
	if (*options & FLAG_N)
		*options |= (FLAG_L);
	if (!(*options & FLAG_L))
		*options &= ~(FLAG_EA);
	if (!((*options & FLAG_L) || (*options & FLAG_T)))
		*options &= ~(FLAG_U);
	if (!((*options & FLAG_L) || (*options & FLAG_T)))
		*options &= ~(FLAG_UU);
	if ((*options & FLAG_F) || (*options & FLAG_SS))
	{
		*options &= ~(FLAG_T);
		*options &= ~(FLAG_C);
		*options &= ~(FLAG_U);
		*options &= ~(FLAG_UU);
	}
	if (*options & FLAG_F)
	{
		*options &= ~(FLAG_SS);
		*options &= ~(FLAG_R);
	}
	check_all_flags1(options);
}		

int	opt_parser(int ac, char **av, int *options)
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
