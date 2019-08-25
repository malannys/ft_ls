/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:36:33 by abartole          #+#    #+#             */
/*   Updated: 2019/08/25 20:40:28 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_symlink(nlink_t st_nlink)
{
	int i;
	int	len;

	len = count_digits(st_nlink);
	i = 3; // will be special function
	while (len < i)
	{
		write(1, " ", 1);
		len++;
	}
	ft_putnbr(st_nlink);
	write(1, " ", 1);
}

static int	get_total(t_node *head, int *options)
{
	t_node	*tmp;
	int		blocks;

	tmp = head;
	blocks = 0;
	while (tmp)
	{
		if (!(FLAG_A & *options) && tmp->name[0] != '.')
			blocks += tmp->stats.st_blocks;
		else if (FLAG_A & *options)
			blocks += tmp->stats.st_blocks;
		tmp = tmp->next;
	}
	return (blocks);
}

static void	print_total(t_node *tmp, int *options)
{
	ft_putstr("total ");
	ft_putnbr(get_total(tmp, options));
	write(1, "\n", 1);
}

static void	print_info(t_node *tmp, int *options)
{
	if (FLAG_I & *options)
			print_inode(tmp);
	type_perm(tmp->path, tmp->stats.st_mode);
	get_symlink(tmp->stats.st_nlink);
	if (!(FLAG_G & *options))
		get_name(tmp->stats.st_uid, options);
	if (!(FLAG_O & *options))
		get_group(tmp->stats.st_gid, options);		
	get_size(tmp->stats.st_size);
	get_time(tmp, options);
	ft_putstr(tmp->name);
	write(1, "\n", 1);
}

void		print_long(char *path, t_node *tmp, int *options)
{
	if (FLAG_RR & *options)
	{
		ft_putstr(path);
		write(1, ":\n", 3);
	}
	print_total(tmp, options);
	while (tmp)
	{
		if (!(FLAG_A & *options) && !(FLAG_AA & *options))
		{
			while (tmp && tmp->name[0] == '.')
				tmp = tmp->next;
		}
		print_info(tmp, options);
		tmp = tmp->next;
	}
	if (FLAG_RR & *options)
		write(1, "\n", 1);
}
