/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:19:37 by malannys          #+#    #+#             */
/*   Updated: 2019/08/24 20:28:55 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_inode(t_node *tmp)
{
	int	len;
	int	i;

	i = 9;
	len = count_digits(tmp->stats.st_ino);
	ft_putnbr(tmp->stats.st_ino);
	while (len < i)
	{
		write (1, " ", 1);
		len++;
	}
	write (1, " ", 1);
}

void	print_l(t_node *head, int *options)
{
	int		i;
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (!(FLAG_A & *options) && !(FLAG_AA & *options))
		{
			while (tmp->name[0] == '.')
					tmp = tmp->next;
		}
		if (FLAG_AA & *options)
		{		
				if ((i = strncmp(tmp->name, "..", 2) == 0) || 
						(i = strncmp(tmp->name, ".", 2)) == 0 )
				tmp = tmp->next;
		}
		if (FLAG_I & *options)
			print_inode(tmp);
		type_perm(tmp->stats.st_mode);
		get_symlink(tmp->stats.st_nlink);
		if (FLAG_L & *options)
			get_name(tmp->stats.st_uid, options);
		get_group(tmp->stats.st_gid, options);		
		get_size(tmp->stats.st_size);
		get_time(tmp, options);
		ft_putendl_fd(tmp->name, 1);
		tmp = tmp->next;
		}
}

void	print_m(t_node *head, int *options)
{
	t_node *tmp;

	tmp = head;
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

void	print_just(t_node *head)
{
	t_node *tmp;
	struct winsize	ws;
	int	len;
	int	i;
	int	col;

	ioctl(1, TIOCGWINSZ, &ws);
	len = 10; //function
	col = ws.ws_col / len;
	tmp = head;
	while(tmp)
	{
		i = 0;
		while (tmp && i < col)
		{
			printf("%-*.*s", len, len, tmp->name);
			tmp = tmp->next;
			i++;
		}
	}
}

void	print(char *path, t_node *head, int *options)
{
	t_node	*tmp;
	int		i;

	tmp = head;
	if (FLAG_ONE & *options)
	{
		ft_putstr_fd(path, 1);
		write(1, ":\n", 3);
		while (tmp && tmp->next)
		{
			ft_putendl_fd(tmp->name, 1);
			tmp = tmp->next;
		}
		write(1, "\n", 2);
	}
	else
	{
		if (!(FLAG_A & *options) && !(FLAG_AA & *options))
		{
			while (tmp->name[0] == '.')
					tmp = tmp->next;
		}
		if (FLAG_AA & *options)
		{		
				if ((i = strncmp(tmp->name, "..", 2) == 0) || 
						(i = strncmp(tmp->name, ".", 2)) == 0 )
				tmp = tmp->next;
		}	
		if ((FLAG_L & *options) || (FLAG_G & *options))
			print_l(tmp, options);
		else if (FLAG_M & *options)
			print_m(tmp, options);
		else
			print_just(tmp);
	}
}
