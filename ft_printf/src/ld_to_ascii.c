/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_to_ascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:54:10 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:55:55 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	cieling(FORMAT *f, char *str, char value)
{
	int i;

	if (value < 5)
		return ;
	i = ft_strlen(str);
	while (--i > -1)
	{
		if (str[i] == '.')
			continue ;
		else if (str[i] == 57)
			str[i] = 48;
		else if (str[i] < 57)
		{
			str[i]++;
			return ;
		}
	}
	f->flags |= PREFFIX;
}

static void	manage_fraction(FORMAT *f, long double val, char *str, size_t size)
{
	if (f->prec == 0)
		cieling(f, str, val * 10);
	else
	{
		str[size++] = '.';
		val = ABS(val);
		while (f->prec-- > 0)
		{
			val *= 10;
			str[size++] = (long)val % 10 + 48;
			val -= (long)val;
		}
		str[size] = '\0';
		cieling(f, str, val * 10);
	}
}

static void	manage_value(FORMAT *f, long value, char *str, size_t size)
{
	str[size] = '\0';
	while (size-- > 0)
	{
		if (f->flags & MINUS)
			str[size] = (value % 10 - 48) * -1;
		else
			str[size] = value % 10 + 48;
		value /= 10;
	}
}

void		ld_to_ascii(FORMAT *f, long double value, size_t size, char *str)
{
	manage_value(f, (long)value, str, size);
	manage_fraction(f, value - (long long)value, str, size);
}
