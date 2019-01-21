/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:46:49 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:48:14 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_hex(FORMAT *f, uintmax_t *hex)
{
	va_list copy;

	if (f->flags & DOLLAR)
	{
		va_copy(copy, f->list);
		while (--f->argnum > 0)
			va_arg(copy, void*);
	}
	if (f->flags & INTMAX || f->flags & LONG1)
		*hex = va_arg((f->flags & DOLLAR) ? copy : f->list, uintmax_t);
	else if (f->flags & LONG || CHAR == 'U')
		*hex = va_arg((f->flags & DOLLAR) ? copy : f->list, unsigned long int);
	else if (f->flags & SHORT)
		*hex = (unsigned short)va_arg((f->flags & DOLLAR) ? copy : f->list,
		unsigned int);
	else if (f->flags & SHORT1)
		*hex = (unsigned char)va_arg((f->flags & DOLLAR) ? copy : f->list,
		unsigned int);
	else if (f->flags & SIZE_T)
		*hex = va_arg((f->flags & DOLLAR) ? copy : f->list, size_t);
	else
		*hex = va_arg((f->flags & DOLLAR) ? copy : f->list, unsigned int);
}

static void	get_size(FORMAT *f, uintmax_t hex, int *size)
{
	*size = (hex == 0) ? 1 : 0;
	while (hex != 0)
	{
		hex /= 16;
		*size += 1;
	}
	if (f->flags & PRECISION)
		*size = (f->prec > *size) ? f->prec : *size;
	if (f->flags & HASH)
		*size += 2;
	if (f->flags & WIDTH && f->flags & ZERO)
		*size = (f->width > *size) ? f->width : *size;
}

static void	print_hex(FORMAT *f, uintmax_t hex, int size)
{
	char value;

	if (size > 0)
	{
		value = hex % 16;
		print_hex(f, hex / 16, --size);
		if (f->flags & PRECISION && f->prec == 0 && hex == 0)
		{
			if (f->width > 0)
			{
				if (f->flags & HASH)
					add_values(f, 32, 2);
				add_char(f, 32);
			}
			return ;
		}
		else if (CHAR == 'x')
			add_char(f, (value > 9) ? value + 87 : value + 48);
		else if (CHAR == 'X')
			add_char(f, (value > 9) ? value + 55 : value + 48);
	}
}

void		manage_hex(FORMAT *f)
{
	int			size;
	uintmax_t	hex;

	get_hex(f, &hex);
	get_size(f, hex, &size);
	if (!(f->flags & ALIGN) && !(f->flags & ZERO))
		add_values(f, 32, f->width - size);
	if (f->flags & HASH && hex != 0)
	{
		add_char(f, '0');
		add_char(f, (CHAR == 'x') ? 'x' : 'X');
	}
	print_hex(f, hex, (f->flags & HASH) ? size - 2 : size);
	if (f->flags & ALIGN && f->width > size)
		add_values(f, 32, f->width - size);
}
