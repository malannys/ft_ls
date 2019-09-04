/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:21:09 by malannys          #+#    #+#             */
/*   Updated: 2019/09/04 21:11:02 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;
}

static int	partition(char **arr, int low, int high)
{
	int 	i;
	int		j;
	int		pivot;

	i = low;
	j = high;
	pivot = (low + high) / 2;
	while (i < j)
	{
		while (ft_strcmp(arr[i], arr[pivot]) < 0)
			i++;
		while (ft_strcmp(arr[j], arr[pivot]) > 0)
			j--;
		if (i >= j)
			return (j);
		swap(&arr[i], &arr[j]);
	}
	return (j);
}

void		ft_quick_sort(char **arr, int low, int high)
{
	int		pivot;

	if (low >= high)
		return ;
	pivot = partition(arr, low, high);
	ft_quick_sort(arr, low, pivot - 1);
	ft_quick_sort(arr, pivot + 1, high);
}
