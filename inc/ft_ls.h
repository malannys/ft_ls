/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:16:46 by malannys          #+#    #+#             */
/*   Updated: 2019/08/24 20:46:29 by abartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
//# include <attr/xattr.h>
# include <time.h>

#include "libft.h"

# define MALLOC_FAILURE 0x1 // exit?
# define LSTAT_FAILURE 0x2
# define OPENDIR_FAILURE 0x4
# define READDIR_FAILURE 0x8
# define CLOSEDIR_FAILURE 0x10
# define GETPWUID_FAILURE 0x20
# define GETGRGID_FAILURE 0x40
# define LISTXATTR_FAILURE 0x80
# define GETXATTR_FAILURE 0x100
# define READLINK_FAILURE 0x200

# define FLAG_ONE 0x1
# define FLAG_AA 0x2
# define FLAG_A 0x4
# define FLAG_BB 0x8
# define FLAG_CC 0x10
# define FLAG_C 0x20 // sort by time of file status changed for -t or -l
# define FLAG_D 0x40
# define FLAG_E 0x80
# define FLAG_FF 0x100
# define FLAG_F 0x200
# define FLAG_GG 0x400
# define FLAG_G 0x800
# define FLAG_I 0x1000
# define FLAG_L 0x2000
# define FLAG_M 0x4000
# define FLAG_N 0x8000
# define FLAG_O 0x10000
# define FLAG_P 0x20000
# define FLAG_Q 0x40000
# define FLAG_RR 0x80000 //recursive search
# define FLAG_R 0x100000 //reverse sorting
# define FLAG_SS 0x200000 //sort by size (largest first)
# define FLAG_TT 0x400000
# define FLAG_T 0x800000 //sort by time modified (recent first) before lexicographical
# define FLAG_U 0x1000000 //sort by time of last access for -t or -l
# define FLAG_UU 0x2000000 //sort by time of creation for -t or -l
# define FLAG_V 0x4000000
# define FLAG_W 0x8000000
# define FLAG_EA 0x10000000
# define FLAG_HH 0x20000000

typedef struct	s_node
{
	char			name[1024];
	char			*path;
	struct stat		stats;
	struct s_node	*next;
}				t_node;

int		opt_parser(int ac, char **av, int *options); // options parser

void	read_dir(char *path, char *name, int *options);
void	dir_recursive(t_node **head, int *options);

void	add_node(char *path, t_node **head, char *name, int *options);
char	*add_path(char *path, char *name);
void	push_back(t_node **head, t_node *node);
void	push_front(t_node **head, t_node *node);
void	free_list(t_node **head);

void	insert_and_sort(t_node **head, t_node *node, int *options);
int		cmp(t_node *node1, t_node *node2, int *options);
int		cmp_lex(char *s1, char *s2, int rev);
int		cmp_time(time_t a, time_t b, char **name, int rev);
int		cmp_size(off_t a, off_t b, char **name, int rev);

void	error(int error_status, char *name);
void	print_errormsg(char *func, char *name);

void	print(char *path, t_node *head, int *options);

#endif
