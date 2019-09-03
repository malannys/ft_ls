/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:40:56 by abartole          #+#    #+#             */
/*   Updated: 2019/09/03 22:20:28 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_string(t_node *tmp)
{
	struct winsize	ws;
	size_t			len;
	int				atty;

	atty = isatty(1);
	ioctl(1, TIOCGWINSZ, &ws);
	len = 0;
	if (atty == 0)
		ws.ws_col = 80;
	while (tmp)
	{
		if (len + ft_strlen(tmp->name) + 3 > ws.ws_col)
		{
			ft_putchar('\n');
			len = 0;
		}
		if (tmp->next)
		{
			ft_putstr(tmp->name);
			ft_putstr(", ");
			len += (ft_strlen(tmp->name) + 2);
		}
		else
			ft_putstr(tmp->name);
		tmp = tmp->next;
	}
	ft_putchar('\n');
}
