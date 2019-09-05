/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 22:12:34 by malannys          #+#    #+#             */
/*   Updated: 2019/09/05 22:12:36 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*add_path(char *path, char *name)
{
	size_t	len1;
	size_t	len2;
	char	*new_path;

	errno = 0;
	if (!name || !path || !ft_strcmp(path, "/"))
		return (ft_strjoin(path, name));
	len1 = ft_strlen(path);
	len2 = ft_strlen(name);
	if ((new_path = (char *)malloc(len1 + len2 + 2)))
	{
		ft_memcpy(new_path, path, len1);
		*(new_path + len1) = '/';
		ft_memcpy(new_path + len1 + 1, name, len2);
		*(new_path + len1 + len2 + 1) = '\0';
	}
	return (new_path);
}
