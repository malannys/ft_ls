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

	if (!head)
		return ;
	tmp = head;
	if (FLAG_ONE & *options)
	{
		ft_putstr_fd(path, 1);
		write(1, ":\n", 3);
		while (tmp)
		{
			ft_putendl_fd(tmp->name, 1);
			tmp = tmp->next;
		}
	}
}
