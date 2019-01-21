/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_adress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:32:33 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:32:34 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_adress(FORMAT *f, long *adr)
{
	va_list copy;

	if (f->flags & DOLLAR)
	{
		va_copy(copy, f->list);
		while (--f->argnum > 0)
			va_arg(copy, void*);
	}
	*adr = va_arg((f->flags & DOLLAR) ? copy : f->list, long);
}

static void	get_size(FORMAT *f, long adr, size_t *size)
{
	*size = (adr == 0) ? 1 : 0;
	while (adr > 0)
	{
		adr /= 16;
		*size += 1;
	}
	if (f->flags & PRECISION)
		*size = (f->prec > *size) ? f->prec : *size;
	if (f->flags & WIDTH && f->flags & ZERO)
		*size = (f->width - 2 > *size) ? f->width - 2 : *size;
}

static void	add_adress(FORMAT *f, long adr, size_t size)
{
	if (f->flags & PRECISION && f->prec == 0)
		return ;
	if (size > 0)
	{
		add_adress(f, adr / 16, --size);
		add_char(f, (adr % 16 > 9) ? adr % 16 + 87 : adr % 16 + 48);
	}
}

void		manage_adress(FORMAT *f)
{
	long	adr;
	size_t	size;

	get_adress(f, &adr);
	get_size(f, adr, &size);
	if (!(f->flags & ALIGN) && !(f->flags & ZERO))
		add_values(f, 32, f->width - size - 2);
	add_char(f, '0');
	add_char(f, 'x');
	add_adress(f, adr, size);
	if (f->flags & ALIGN)
		add_values(f, 32, f->width - size - 2);
}
