/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:40:56 by abartole          #+#    #+#             */
/*   Updated: 2019/08/25 16:48:55 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_string(t_node *tmp, int *options)
{
	while (tmp)
	{		
		if (FLAG_I & *options)
			print_inode(tmp);
		ft_putstr(tmp->name);
		if (tmp->next)
		{			
			write(1, ",", 1);
			write(1, " ", 1);
		}
		else
			write (1, "\n", 1);
		tmp = tmp->next;
	}
}
