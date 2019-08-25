/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 21:00:14 by abartole          #+#    #+#             */
/*   Updated: 2019/08/25 20:23:07 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_options2(char *str, int *options)
{
	if (*str == 'q')
	{
		*options &= ~(FLAG_BB);
		*options &= ~(FLAG_W);
	}
	else if (*str == 'n')
		*options &= ~(FLAG_L);
	else if (*str == 'u')
		*options &= ~(FLAG_C);
}

static void	check_options1(char *str, int *options)
{
	if (*str == 'm')
	{
		*options &= ~(FLAG_L);
		*options &= ~(FLAG_CC);
		*options &= ~(FLAG_ONE);
	}
	else if (*str == 'c')
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
	check_options2(str, options);
}

void		check_options(char *str, int *options)
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
	check_options1(str, options);
}

static void	check_all_flags1(int *options)
{
	if (*options & FLAG_F)
		*options &= ~(FLAG_SS);
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

void		check_all_flags(int *options)
{
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
		*options &= ~(FLAG_R);
	}
	check_all_flags1(options);
}
