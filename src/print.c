/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:19:37 by malannys          #+#    #+#             */
/*   Updated: 2019/08/21 19:35:56 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print(char *path, t_node *head, int *options)
{
	t_node	*tmp;

	if (FLAG_RR & *options)
	{
		ft_putstr(path);
		write(1, ":\n", 2);
	}
	if (!head) // don't forget to check for null!!
		return ;
	tmp = head;
	if (FLAG_ONE & *options)
	{
		while (tmp)
		{
			ft_putendl_fd(tmp->name, 1);
			tmp = tmp->next;
		}
	}
	if (0) // for not having unused parameter error
		ft_putstr(path);
}
