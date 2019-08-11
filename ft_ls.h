/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:16:46 by malannys          #+#    #+#             */
/*   Updated: 2019/08/11 19:20:08 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
//#include <attr/xattr.h>
#include <time.h>

typedef struct	s_node
{
	char			path[1024];
	struct stat		stats;
	struct s_node	*next;
}				t_node;

int		opt_parser(int ac, char **av, int *options); // options parser
void	ft_ls(char *av, int options); //

#endif
