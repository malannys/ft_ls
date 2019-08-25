/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_perm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:27:37 by abartole          #+#    #+#             */
/*   Updated: 2019/08/25 20:14:45 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	acl_info(char *path)
{
	acl_t	tmp;

	if (listxattr(path, 0, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((tmp = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp);
		return ('+');
	}
	return (' ');
}

static char	get_filetype(mode_t st_mode)
{
	if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISSOCK(st_mode))
		return ('s');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISLNK(st_mode))
		return ('l');
	else
		return ('-');
}

void		type_perm(char *path, mode_t st_mode)
{
	char	tab[11];

	tab[0] = get_filetype(st_mode);
	tab[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	tab[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	tab[3] = (st_mode & S_IXUSR) ? 'x' : '-';
	tab[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	tab[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	tab[6] = (st_mode & S_IXGRP) ? 'x' : '-';
	tab[7] = (st_mode & S_IROTH) ? 'r' : '-';
	tab[8] = (st_mode & S_IWOTH) ? 'w' : '-';
	tab[9] = (st_mode & S_IXOTH) ? 'x' : '-';
	if (st_mode & S_ISUID)
		tab[3] = (st_mode & S_IXUSR) ? 's' : 'S';
	if (st_mode & S_ISGID)
		tab[6] = (st_mode & S_IXGRP) ? 's' : 'l';
	if (st_mode & S_ISVTX)
		tab[9] = (st_mode & S_IXOTH) ? 't' : 'T';
	tab[10] = acl_info(path);
	write(1, &tab, 11);
	write(1, " ", 1);
}
