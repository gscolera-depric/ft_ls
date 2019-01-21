/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:52:37 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:53:41 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_unsigned(FORMAT *f, uintmax_t *un)
{
	va_list copy;

	if (f->flags & DOLLAR)
	{
		va_copy(copy, f->list);
		while (--f->argnum > 0)
			va_arg(copy, void*);
	}
	if (f->flags & INTMAX || f->flags & LONG1)
		*un = va_arg((f->flags & DOLLAR) ? copy : f->list, uintmax_t);
	else if (f->flags & LONG || CHAR == 'U')
		*un = va_arg((f->flags & DOLLAR) ? copy : f->list, unsigned long int);
	else if (f->flags & SHORT)
		*un = (unsigned short)va_arg((f->flags & DOLLAR) ? copy : f->list,
		unsigned int);
	else if (f->flags & SHORT1)
		*un = (unsigned char)va_arg((f->flags & DOLLAR) ? copy : f->list,
		unsigned int);
	else if (f->flags & SIZE_T)
		*un = va_arg((f->flags & DOLLAR) ? copy : f->list, size_t);
	else
		*un = va_arg((f->flags & DOLLAR) ? copy : f->list, unsigned int);
}

static void	get_size(FORMAT *f, uintmax_t un, int *size)
{
	*size = (un == 0) ? 1 : 0;
	while (un != 0)
	{
		un /= 10;
		*size += 1;
	}
	if (f->flags & PRECISION)
		*size = (f->prec > *size) ? f->prec : *size;
	if (f->flags & WIDTH && f->flags & ZERO)
		*size = (f->width > *size) ? f->width : *size;
}

static void	print_unsigned(FORMAT *f, uintmax_t un, int size)
{
	if (size > 0)
	{
		if (f->flags & PRECISION && f->prec == 0 && un == 0)
		{
			if (f->width > 0)
				add_char(f, 32);
			return ;
		}
		print_unsigned(f, un / 10, --size);
		add_char(f, un % 10 + 48);
	}
}

void		manage_unsigned(FORMAT *f)
{
	int			size;
	uintmax_t	un;

	get_unsigned(f, &un);
	get_size(f, un, &size);
	if (!(f->flags & ALIGN) && !(f->flags & ZERO))
		add_values(f, 32, f->width - size);
	print_unsigned(f, un, size);
	if (f->flags & ALIGN)
		add_values(f, 32, f->width - size);
}
