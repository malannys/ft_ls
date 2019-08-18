/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:16:49 by malannys          #+#    #+#             */
/*   Updated: 2019/08/17 18:52:07 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		error(int error_status, int errno, char *name)
{
	if (error_status == MALLOC_FAILURE)
	{
		perror("ls: malloc: ");
		exit(EXIT_FAILURE);
	}
	else if (error_status == LSTAT_FAILURE)
		perror("ls: lstat: ");
	else if (error_status == READDIR_FAILURE) //dirname
		perror("ls: readdir: ");
	else if (error_status == OPENDIR_FAILURE) //dirname
		perror("ls: opendir: ");
	else if (error_status == CLOSEDIR_FAILURE) //dirname
		perror("ls: closedir: ");
	else if (error_status == GETPWUID_FAILURE)
		perror("ls: getpwuid: ");
	else if (error_status == GETGRGID_FAILURE)
		perror("ls: getgrgid: ");
	else if (error_status == LISTXATTR_FAILURE)
		perror("ls: listxattr: ");
	else if (error_status == GETXATTR_FAILURE)
		perror("ls: getxattr: ");
	else if (error_status == READLINK_FAILURE)
		perror("ls: readlink: ");
	return (-1);
}
