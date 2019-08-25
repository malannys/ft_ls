/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_for_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:50:49 by abartole          #+#    #+#             */
/*   Updated: 2019/08/25 20:32:08 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		count_digits(int n)
{
	int i;

	i = 0;
	while (n / 10 > 0)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

void	get_size(off_t st_size)
{
	int	i;
	int	len;

	i = 7; //Count max len
	len = count_digits(st_size);
	while (len < i)
	{
		write (1, " ", 1);
		len++;
	}
	ft_putnbr(st_size);
	write(1, " ", 1);
}

void	get_group(gid_t st_gid, int *options)
{
	struct group	*group;
	int	len;
	int	i;

	i = 5; //Count max len
	group = getgrgid(st_gid);
	len = (FLAG_N & *options) ? count_digits(group->gr_gid) :
		ft_strlen(group->gr_name);
	(FLAG_N & *options) ? ft_putnbr(group->gr_gid) :
		write(1, group->gr_name, len);
	while (len < i)
	{
		write(1, " ", 1);
		len++;
	}
}

void	get_name(uid_t st_uid, int *options)
{
	struct passwd	*name;
	int	len;
	int	i;

	name = getpwuid(st_uid);
	len = (FLAG_N & *options) ? count_digits(name->pw_uid) :
		ft_strlen(name->pw_name);
	i = 10; //count max len
	(FLAG_N & *options) ? ft_putnbr(name->pw_uid) :
		ft_putstr(name->pw_name);
	while (len < i)
	{
		write(1, " ", 1);
		len++;
	}
}

void	get_time(t_node *tmp, int *options)
{
	char	*time;

	if (FLAG_U & *options)
		time = ft_strsub(ctime(&tmp->stats.st_atime),
				(unsigned int)4, (size_t)12);
	else if (FLAG_UU & *options)
		time = ft_strsub(ctime(&tmp->stats.st_birthtime),
				(unsigned int)4, (size_t)12);
	else
		time = ft_strsub(ctime(&tmp->stats.st_mtime),
				(unsigned int)4, (size_t)12);
	ft_putstr(time);
	write(1, " ", 1);
}
