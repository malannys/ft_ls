/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:16:49 by malannys          #+#    #+#             */
/*   Updated: 2019/08/21 19:40:04 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_errormsg(char *func, char *name)
{
	char	*errorbuff;

	ft_putstr("ft_ls: ");
	ft_putstr(func);
	ft_putstr(": ");
	ft_putstr(name);
	ft_putstr(": ");
	if ((errorbuff = strerror(errno)))
		ft_putstr(errorbuff);
	write(2, "\n", 1);
}

void	error(int error_status, char *name)
{
	if (error_status == MALLOC_FAILURE)
	{
		perror("ft_ls: malloc: ");
		exit(EXIT_FAILURE);
	}
	else if (error_status == LSTAT_FAILURE)
		print_errormsg("lstat", name);
	else if (error_status == READDIR_FAILURE)
		print_errormsg("readdir", name);
	else if (error_status == OPENDIR_FAILURE)
		print_errormsg("opendir", name);
	else if (error_status == CLOSEDIR_FAILURE)
		print_errormsg("closedir", name);
	else if (error_status == GETPWUID_FAILURE)
		perror("ft_ls: getpwuid");
	else if (error_status == GETGRGID_FAILURE)
		perror("ft_ls: getgrgid");
	else if (error_status == LISTXATTR_FAILURE)
		perror("ft_ls: listxattr");
	else if (error_status == GETXATTR_FAILURE)
		perror("ft_ls: getxattr");
	else if (error_status == READLINK_FAILURE)
		perror("ft_ls: readlink");
}
