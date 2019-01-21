/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_length.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 16:14:20 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 16:14:20 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strlen(const char *str)
{
	char *ptr;

	if (!str)
		return (0);
	ptr = (char*)str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}

int		ft_wchar_len(wchar_t c)
{
	if (c < 0x80)
		return (1);
	else if (c < 0x800)
		return (2);
	else if (c < 0x10000)
		return (3);
	else
		return (4);
}

int		ft_wstr_len(wchar_t *wstr)
{
	int count;

	count = 0;
	while (*wstr)
	{
		count += ft_wchar_len(*wstr);
		wstr++;
	}
	return (count);
}

size_t	ft_numlen(int nbr)
{
	size_t size;

	size = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		size++;
	while (nbr != 0)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}
