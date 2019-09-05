/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:16:46 by malannys          #+#    #+#             */
/*   Updated: 2019/09/05 21:05:53 by abartole         ###   ########.fr       */
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
# include <sys/xattr.h>
# include <time.h>
# include <sys/ioctl.h>
# include <sys/acl.h>

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

# define FLAG_ONE 0x1 // Force output to be one entry per line.
# define FLAG_AA 0x2 // List all entries except for . and ...  Always set for the super-user.
# define FLAG_A 0x4 // Include directory entries whose names begin with a dot (.).
# define FLAG_CC 0x8 // Force multi-column output; this is the default when output is to a terminal.
# define FLAG_C 0x10 // sort by time of file status changed for -t or -l
# define FLAG_F 0x20 // Output is not sorted.  This option turns on the -a option.
# define FLAG_G 0x40 // Display the group name in the long (-l) format output (the owner name is suppressed).
# define FLAG_L 0x80 // List in long format.
# define FLAG_M 0x100 // Stream output format; list files across the page, separated by commas.
# define FLAG_N 0x200 // Display user and group IDs numerically.
# define FLAG_O 0x400 // List in long format, but omit the group id.
# define FLAG_RR 0x800 //recursive search
# define FLAG_R 0x1000 //reverse sorting
# define FLAG_SS 0x2000 //sort by size (largest first)
# define FLAG_TT 0x4000 // Display complete time information for the file, including month, day, hour, minute, second, and year.
# define FLAG_T 0x8000 //sort by time modified (recent first) before lexicographical
# define FLAG_U 0x10000 //sort by time of last access for -t or -l
# define FLAG_UU 0x20000 //sort by time of creation for -t or -l
# define FLAG_EA 0x40000 // Display extended attribute keys and sizes in long (-l) output.
# define FLAG_HH 0x80000 // Symbolic links on the command line are followed.  This option is assumed if none of the -F, -d, or -l options are specified.
// -L	Follow all symbolic links to final target and list the file or directory the link references rather than the link itself.  This option cancels the -P option.
// -P	If argument is a symbolic link, list the link itself rather than the object the link references.  This option cancels the -H and -L options.

# define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef enum	e_maxlen
{
	MAX_INO,
	MAX_LNK,
	MAX_UID,
	MAX_GID,
	MAX_SZ,
	MAX_PWD,
	MAX_GP
}				t_maxlen;

typedef struct	s_node
{
	char			name[1024];
	char			*path;
	struct stat		stats;
	struct s_node	*next;
	struct s_node	*tail;
}				t_node;

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

/*
** Parsing options
*/

void	check_options(char *str, int *options);
void	check_all_flags(int *options);
int		opt_parser(int ac, char **av, int *options);

/*
** Printing
*/

void	print_long(t_node *tmp, int *options);
void	print_string(t_node *tmp);
void	print_default(t_node *head);
void	print_column(t_node *tmp);
void	print(char *path, t_node *head, int *options);

/*
** Information for long format
*/

void	print_link(t_node *tmp);
void	print_total(t_node *head, int *options);
void	get_symlink(nlink_t st_nlink, int maxlen);
void	print_info(t_node *tmp, int *maxlen, int *options);
void	print_attr(t_node *tmp, int	*options);
void	type_perm(char *path, mode_t st_mode);
int		get_maxlen_name(t_node *tmp);
void	get_maxlen_user(t_node *tmp, int *max, int *options);
void	get_maxlen_group(t_node *tmp, int *max, int *options);
void	get_maxlen(t_node *tmp, int *max, int *options);
void	get_time(t_node *tmp, int *options);
void	get_name(t_node *tmp, int *options, int *maxlen);
void	get_group(t_node *tmp, int *options, int *maxlen);
void	get_size(t_node *tmp, int maxlen);
int		nb_len(long long n);


void	read_args(int ac, char **av, int *options, int arg);
void	read_dir(char *path, t_node *node, int *options);
void	dir_recursive(t_node **head, int *options);

t_node	*create_node(char *path, char *name, int *options, int follow_link);
char	*add_path(char *path, char *name);
void	push_back(t_node **head, t_node *node);
void	push_front(t_node **head, t_node *node);
void	free_list(t_node **head);

void	sort(t_node **head, t_node **tail, int *options);
void	append(t_node **head, t_node **tail, t_node *tmp);
void	lst_join(t_node **head1, t_node **tail1, t_node **head2, t_node **tail2);
//void	insert_and_sort(t_node **head, t_node *node, int *options);
int		cmp(t_node *node1, t_node *node2, int *options);
int		cmp_lex(char *s1, char *s2, int rev);
int		cmp_time(time_t a, time_t b, char **name, int rev);
int		cmp_size(off_t a, off_t b, char **name, int rev);

/*
** Error handling
*/

int		error_managment(char *src, char *str, int error);
void	error(int error_status, char *name);
void	print_errormsg(char *name);

#endif
