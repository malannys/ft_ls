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

void	get_maxlen_user(t_node *tmp, int *max, int *options)
{
	struct passwd	*pwd;

	errno = 0;
	if (!(pwd = getpwuid(tmp->stats.st_uid)))
	{
		error(GETPWUID_FAILURE, tmp->name);
		return ;
	}
	if (FLAG_N & *options)
		max[MAX_UID] = MAX(nb_len(pwd->pw_uid), max[MAX_UID]);
	else
		max[MAX_PWD] = MAX((int)ft_strlen(pwd->pw_name), max[MAX_PWD]);
}

void	get_maxlen_group(t_node *tmp, int *max, int *options)
{
	struct group	*gp;

	errno = 0;
	if (!(gp = getgrgid(tmp->stats.st_gid)))
	{
		error(GETGRGID_FAILURE, tmp->name);
		return ;
	}
	if (FLAG_N & *options)
		max[MAX_GID] = MAX(nb_len(gp->gr_gid), max[MAX_GID]);
	else
		max[MAX_GP] = MAX((int)ft_strlen(gp->gr_name), max[MAX_GP]);
}

void	get_maxlen(t_node *tmp, int *max, int *options)
{
	while (tmp)
	{
		max[MAX_LNK] = MAX(nb_len(tmp->stats.st_nlink), max[MAX_LNK]);
		max[MAX_SZ] = MAX(nb_len(tmp->stats.st_size), max[MAX_SZ]);
		if (FLAG_I & *options)
			max[MAX_INO] = MAX(nb_len(tmp->stats.st_ino), max[MAX_INO]);
		if (!(FLAG_G & *options))
			get_maxlen_user(tmp, max, options);
		if (!(FLAG_O & *options))
			get_maxlen_group(tmp, max, options);
		tmp = tmp->next;
	}
}

int		nb_len(long long n)
{
	int	i;

	i = 1;
	while ((n = n / 10))
		i++;
	return (i);
}

void	get_size(off_t st_size, int maxlen)
{
	int	len;

	len = nb_len(st_size);
	while (len < maxlen)
	{
		write (1, " ", 1);
		len++;
	}
	ft_putnbr(st_size);
	write(1, " ", 1);
}

void	get_group(t_node *tmp, int *options, int *maxlen)
{
	int				len;
	int				i;
	struct group	*gp;

	gp = getgrgid(tmp->stats.st_gid);
	if (FLAG_N & *options)
	{
		len = nb_len(gp->gr_gid);
		i = maxlen[MAX_GID] + 2;
		ft_putnbr(gp->gr_gid);
	}
	else
	{
		len = ft_strlen(gp->gr_name);
		i = maxlen[MAX_GP] + 2;
		write(1, gp->gr_name, len);
	}
	while (len < i)
	{
		write(1, " ", 1);
		len++;
	}
}

void	get_name(t_node *tmp, int *options, int *maxlen)
{
	int				len;
	int				i;
	struct passwd	*pwd;

	pwd = getpwuid(tmp->stats.st_uid);
	if (FLAG_N & *options)
	{
		len = nb_len(pwd->pw_uid);
		i = maxlen[MAX_UID] + 2;
		ft_putnbr(pwd->pw_uid);
	}
	else
	{
		len = ft_strlen(pwd->pw_name);
		i = maxlen[MAX_PWD] + 2;
		write(1, pwd->pw_name, len);
	}
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
