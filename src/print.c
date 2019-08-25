/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:23:15 by abartole          #+#    #+#             */
/*   Updated: 2019/08/25 20:39:30 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_inode(t_node *tmp)
{
	int	len;
	int	i;

	i = 7;
	len = count_digits(tmp->stats.st_ino);
	while (len < i)
	{
		write (1, " ", 1);
		len++;
	}
	ft_putnbr(tmp->stats.st_ino);
	write (1, " ", 1);
}

void	print(char *path, t_node *head, int *options)
{
	t_node	*tmp;

	tmp = head;
	if (!(FLAG_A & *options) && !(FLAG_AA & *options))
	{
		while (tmp && tmp->name[0] == '.')
			tmp = tmp->next;
	}
	if (FLAG_M & *options)
		print_string(tmp, options);
	else if ((FLAG_L & *options) || (FLAG_G & *options) ||
			(FLAG_O & *options) || (FLAG_L & *options))
		print_long(path, tmp, options);
	//else if (FLAG_ONE & *options)
		//print_column(tmp, options);
	//else
		//print_default(tmp, options);
}
