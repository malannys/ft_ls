/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:19:51 by malannys          #+#    #+#             */
/*   Updated: 2019/08/17 18:52:15 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** Sort by lexicographic order
*/
int		cmp_lex(char *s1, char *s2, int rev)
{
	if (rev)
		return (ft_strcmp(node1->name, node2->name) >= 0)
	return (ft_strcmp(node1->name, node2->name) <= 0)
}

/*
** Sort by time of:
** -t: last modification
** -c: last file status change
** -u: last access
** -U: file creation
*/
int		cmp_time(t_time a, t_time b, char **name, int rev)
{
	if (IS_EQUAL(a, b))
		return (cmp_lex(name[1], name[2], rev));
	if (rev)
		return (IS_MAX(a, b) ? 1 : 0);
	return (IS_MIN(a, b) ? 1 : 0);
}

/*
** Sort by size (biggest first)
*/
int		cmp_size(off_t a, off_t b, int rev)
{
	if (IS_EQUAL(a, b))
		return (cmp_lex(name[1], name[2], rev));
	if (rev)
		return (IS_MAX(a, b) ? 1 : 0);
	return (IS_MIN(a, b) ? 1 : 0);
}

int		cmp(t_node *node1, t_node *node2, int *options)
{
	int		rev;
	char	*name[2];

	tmp = *head;
	name[1] = node1->name;
	name[2] = node2->name;
	rev = (FLAG_RR & *options) ? 1 : 0;
	if (FLAG_SS & *options)
		return (cmp_size(node1->st_size, node2->st_size, name, rev));
	else if (FLAG_T & *options)
		return (cmp_time(node1->st_mtime, node2->st_mtime, name, rev));
	else if (FLAG_C & *options)
		return (cmp_time(node1->st_ctime, node2->st_ctime, name, rev));
	else if (FLAG_U & *options)
		return (cmp_time(node1->st_atime, node2->st_atime, name, rev));
	else if (FLAG_UU & *options)
		return (cmp_time(node1->st_birthtime, node2->st_birthtime, name, rev)); // ????? crtime or birthtime
	else
		return (cmp_lex(node1->name, node2->name, rev));
}

void	insert_and_sort(t_node **head, t_node *node, int *options)
{
	t_node	*tmp;
	t_node	*swap;

	tmp = *head;
	if (FLAG_FF & *options)
	{
		push_back(head, node);
		return ;
	}
	push_front(head, node);
	tmp = *head;
	while (tmp->next && !cmp(tmp, tmp->next, options))
	{
		swap = tmp->next;
		tmp->next = swap->next;
		swap->next = tmp;
		if (tmp == *head)
			*head = swap;
		tmp = tmp->next;
	}
}
