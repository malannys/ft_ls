/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:57:11 by abartole          #+#    #+#             */
/*   Updated: 2019/09/03 22:28:54 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print(char *path, t_node *head, int *options)
{
	if (path && 0)
	{
		ft_putstr_fd(path, 1);
		write(1, ":\n", 3);
	}
	if (!head)
		return ;
	if (FLAG_M & *options)
		print_string(head);
	else if ((FLAG_L & *options) || (FLAG_G & *options) ||
			(FLAG_O & *options) || (FLAG_L & *options))
		print_long(head, options);
	else if (FLAG_ONE & *options)
		print_column(head);
	else
		print_default(head);
}
