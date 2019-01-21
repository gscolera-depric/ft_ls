/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_octal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:48:21 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:50:50 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_octal(FORMAT *f, uintmax_t *oc)
{
	va_list copy;

	if (f->flags & DOLLAR)
	{
		va_copy(copy, f->list);
		while (--f->argnum > 0)
			va_arg(copy, void*);
	}
	if (f->flags & INTMAX || f->flags & LONG1)
		*oc = va_arg((f->flags & DOLLAR) ? copy : f->list, uintmax_t);
	else if (f->flags & LONG || CHAR == 'O')
		*oc = va_arg((f->flags & DOLLAR) ? copy : f->list, unsigned long int);
	else if (f->flags & SHORT)
		*oc = (unsigned short)va_arg((f->flags & DOLLAR) ? copy : f->list,
		unsigned int);
	else if (f->flags & SHORT1)
		*oc = (unsigned char)va_arg((f->flags & DOLLAR) ? copy : f->list,
		unsigned int);
	else if (f->flags & SIZE_T)
		*oc = va_arg((f->flags & DOLLAR) ? copy : f->list, size_t);
	else
		*oc = va_arg((f->flags & DOLLAR) ? copy : f->list, unsigned int);
}

static void	get_size(FORMAT *f, uintmax_t oc, int *size)
{
	*size = (oc == 0) ? 1 : 0;
	if (f->flags & HASH && oc != 0)
		*size += 1;
	while (oc != 0)
	{
		oc /= 8;
		*size += 1;
	}
	if (f->flags & WIDTH && f->flags & ZERO)
		*size = (f->width > *size) ? f->width : *size;
	if (f->flags & PRECISION)
		*size = (f->prec > *size) ? f->prec : *size;
}

static void	print_octal(FORMAT *f, uintmax_t oc, int size)
{
	if (size > 0)
	{
		if (f->flags & PRECISION && f->prec == 0 && oc == 0)
		{
			if (f->width > 0)
				add_char(f, 32);
			if (f->flags & HASH)
				add_char(f, 48);
			return ;
		}
		print_octal(f, oc / 8, --size);
		add_char(f, oc % 8 + 48);
	}
}

void		manage_octal(FORMAT *f)
{
	int			size;
	uintmax_t	oc;

	get_octal(f, &oc);
	get_size(f, oc, &size);
	if (!(f->flags & ALIGN) && !(f->flags & ZERO))
		add_values(f, 32, f->width - size);
	print_octal(f, oc, size);
	if (f->flags & ALIGN && f->width > size)
		add_values(f, 32, f->width - size);
}
