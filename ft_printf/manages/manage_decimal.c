/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:43:32 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:44:07 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_decimal(FORMAT *f, intmax_t *decimal)
{
	va_list copy;

	if (f->flags & DOLLAR)
	{
		va_copy(copy, f->list);
		while (--f->argnum > 0)
			va_arg(copy, void*);
	}
	if (f->flags & INTMAX)
		*decimal = va_arg((f->flags & DOLLAR) ? copy : f->list, intmax_t);
	else if (f->flags & SIZE_T)
		*decimal = va_arg((f->flags & DOLLAR) ? copy : f->list, size_t);
	else if (f->flags & LONG || CHAR == 'D')
		*decimal = va_arg((f->flags & DOLLAR) ? copy : f->list, long int);
	else if (f->flags & LONG1)
		*decimal = va_arg((f->flags & DOLLAR) ? copy : f->list, long long int);
	else if (f->flags & SHORT)
		*decimal = (short)va_arg((f->flags & DOLLAR) ? copy : f->list, int);
	else if (f->flags & SHORT1)
		*decimal = (char)va_arg((f->flags & DOLLAR) ? copy : f->list, int);
	else
		*decimal = va_arg((f->flags & DOLLAR) ? copy : f->list, int);
}

static void	get_size(FORMAT *f, intmax_t decimal, int *size)
{
	_Bool sign;

	if (decimal < 0)
		f->flags |= MINUS;
	*size = (decimal == 0) ? 1 : 0;
	while (decimal != 0)
	{
		decimal /= 10;
		*size += 1;
	}
	if (f->flags & PRECISION)
		*size = (f->prec > *size) ? f->prec : *size;
	if (f->flags & PLUS || f->flags & SPACE || f->flags & MINUS)
		*size += 1;
	if (f->flags & WIDTH && f->flags & ZERO)
		*size = (f->width > *size) ? f->width : *size;
}

static void	print_decimal(FORMAT *f, intmax_t decimal, int size)
{
	if (size > 0)
	{
		print_decimal(f, decimal / 10, --size);
		if (f->flags & PRECISION && f->prec == 0 && decimal == 0)
		{
			if (f->width > 0)
				add_char(f, 32);
			return ;
		}
		if (decimal < 0)
			add_char(f, -(decimal % 10 - 48));
		else
			add_char(f, decimal % 10 + 48);
	}
}

void		manage_decimal(FORMAT *f)
{
	_Bool		sign;
	int			size;
	intmax_t	decimal;

	get_decimal(f, &decimal);
	get_size(f, decimal, &size);
	sign = (f->flags & PLUS || f->flags & SPACE || f->flags & MINUS) ? 1 : 0;
	if (!(f->flags & ALIGN) && !(f->flags & ZERO))
		add_values(f, 32, f->width - size);
	if (sign)
	{
		add_sign(f);
		print_decimal(f, decimal, --size);
	}
	else
		print_decimal(f, decimal, size);
	if (f->flags & ALIGN)
		add_values(f, 32, (sign) ? f->width - size - 1 : f->width - size);
}
