/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:44:13 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:46:39 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_double(FORMAT *f, long double *d)
{
	va_list copy;

	if (f->flags & DOLLAR)
	{
		va_copy(copy, f->list);
		while (--f->argnum > 0)
			va_arg(copy, void*);
	}
	if (f->flags & LONG2)
		*d = va_arg((f->flags & DOLLAR) ? copy : f->list, long double);
	else
		*d = va_arg((f->flags & DOLLAR) ? copy : f->list, double);
}

static void	get_size(FORMAT *f, long d, size_t *size)
{
	*size = (d == 0) ? 1 : 0;
	while (d != 0)
	{
		d /= 10;
		*size += 1;
	}
}

static void	print_double(FORMAT *f, long double d, size_t size)
{
	char value[size + f->prec + 2];

	ld_to_ascii(f, d, size, value);
	size = ft_strlen(value);
	if (f->flags & PLUS || f->flags & SPACE || f->flags & MINUS)
		size++;
	if (f->flags & PREFFIX)
		size++;
	if (f->width > size && !(f->flags & ALIGN) && !(f->flags & ZERO))
		add_values(f, 32, f->width - size);
	if (f->flags & PLUS || f->flags & SPACE || f->flags & MINUS)
		add_sign(f);
	if (f->flags & PREFFIX)
		add_char(f, 49);
	if (f->width > size && !(f->flags & ALIGN) && f->flags & ZERO)
		add_values(f, 48, f->width - size);
	add_string(f, value);
	if (f->width > size && f->flags & ALIGN)
		add_values(f, 32, f->width - size);
}

void		manage_double(FORMAT *f)
{
	size_t			size;
	long double		d;

	get_double(f, &d);
	if (d < 0)
		f->flags |= MINUS;
	get_size(f, d, &size);
	print_double(f, d, size);
}
