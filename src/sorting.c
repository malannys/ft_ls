/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:19:51 by malannys          #+#    #+#             */
/*   Updated: 2019/08/21 19:32:42 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Sort by lexicographic order
*/
int		cmp_lex(char *s1, char *s2, int rev)
{
	if (rev)
		return (ft_strcmp(s1, s2) >= 0);
	return(ft_strcmp(s1, s2) <= 0);
}

/*
** Sort by time of:
** -t: last modification
** -c: last file status change
** -u: last access
** -U: file creation
*/
int		cmp_time(time_t a, time_t b, char **name, int rev)
{
	if (a == b)
		return (cmp_lex(name[0], name[1], rev));
	if (rev)
		return (a < b ? 1 : 0);
	return (a > b ? 1 : 0);
}

/*
** Sort by size (biggest first)
*/
int		cmp_size(off_t a, off_t b, char **name, int rev)
{
	if (a == b)
		return (cmp_lex(name[0], name[1], rev));
	if (rev)
		return (a < b ? 1 : 0);
	return (a > b ? 1 : 0);
}

int		cmp(t_node *node1, t_node *node2, int *options)
{
	int		rev;
	char	*name[2];

	name[0] = node1->name;
	name[1] = node2->name;
	rev = (FLAG_R & *options) ? 1 : 0;
	if (FLAG_SS & *options)
		return (cmp_size(node1->stats.st_size, node2->stats.st_size, name, rev));
	else if ((FLAG_U & *options) && (FLAG_T & *options))
		return (cmp_time(node1->stats.st_atime, node2->stats.st_atime, name, rev));
	else if ((FLAG_UU & *options) && (FLAG_T & *options))
		return (cmp_time(node1->stats.st_birthtime, node2->stats.st_birthtime, name, rev));
	else if ((FLAG_C & *options) && (FLAG_T & *options))
		return (cmp_time(node1->stats.st_ctime, node2->stats.st_ctime, name, rev));
	else if (FLAG_T & *options)
		return (cmp_time(node1->stats.st_mtime, node2->stats.st_mtime, name, rev));
	else
		return (cmp_lex(node1->name, node2->name, rev));
}

void	insert_and_sort(t_node **head, t_node *node, int *options)
{
	t_node	*tmp;
	t_node	*swap;
	t_node	*prev;

	if (FLAG_F & *options)
	{
		push_back(head, node);
		return ;
	}
	push_front(head, node);
	prev = *head;
	tmp = *head;
	while (tmp && tmp->next && !cmp(tmp, tmp->next, options))
	{
		swap = tmp->next;
		tmp->next = swap->next;
		swap->next = tmp;
		if (tmp == *head)
			*head = swap;
		else
			prev->next = swap;
		prev = swap;
	}
}
