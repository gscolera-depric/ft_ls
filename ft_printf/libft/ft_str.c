/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 16:14:31 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/19 21:15:58 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnew(size_t size)
{
	char *new;

	if (size == 0 || size == (size_t)-1)
		return (NULL);
	if (!(new = (char*)malloc(size + 1)))
		return (NULL);
	new[size] = '\0';
	while (size-- > 0)
		new[size] = '\0';
	return (new);
}

char	*ft_strdup(const char *str)
{
	char	*new;
	int		i;

	if (!str)
		return (NULL);
	if (!(new = ft_strnew(ft_strlen(str))))
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	return (new);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tmp;
	int		fi;
	int		si;

	if (!s1 && !s2)
		return (NULL);
	if (!(tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	fi = -1;
	while (s1[++fi])
		tmp[fi] = s1[fi];
	si = -1;
	while (s2[++si])
		tmp[fi++] = s2[si];
	return (tmp);
}

_Bool	ft_strequ(const char *str1, const char *str2)
{
	int i;

	i = 0;
	if (!str1)
		return ((str2) ? 0 : 1);
	while (str1[i] && str1[i] == str2[i])
		i++;
	return ((str1[i] - str2[i] == 0) ? 1 : 0);
}

void	ft_strdel(char **str)
{
	free(*str);
	*str = NULL;
}
