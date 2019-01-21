/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:57:32 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:59:21 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_digits(FORMAT *f)
{
	int value;

	if (CHAR == 48)
	{
		f->flags |= ZERO;
		return ;
	}
	value = 0;
	while (DIGIT(CHAR))
	{
		value = value * 10 + CHAR - 48;
		NEXT;
	}
	if (CHAR == '$')
	{
		f->flags |= DOLLAR;
		f->argnum = value;
	}
	else
	{
		f->flags |= WIDTH;
		f->width = value;
		PREVIOUS;
	}
}

static void	parse_precision(FORMAT *f)
{
	NEXT;
	f->flags |= PRECISION;
	if (CHAR == '*')
		f->prec = va_arg(f->list, int);
	else
	{
		while (DIGIT(CHAR))
		{
			f->prec = f->prec * 10 + CHAR - 48;
			NEXT;
		}
		PREVIOUS;
	}
	if (f->prec < 0)
	{
		f->prec = 0;
		f->flags ^= PRECISION;
	}
}

static void	parse_size(FORMAT *f)
{
	if (CHAR == 'l' && N_CHAR != 'l')
		f->flags |= LONG;
	else if (CHAR == 'l' && N_CHAR == 'l' && NEXT)
		f->flags |= LONG1;
	else if (CHAR == 'L')
		f->flags |= LONG2;
	else if (CHAR == 'h' && N_CHAR != 'h')
		f->flags |= SHORT;
	else if (CHAR == 'h' && N_CHAR == 'h' && NEXT)
		f->flags |= SHORT1;
	else if (CHAR == 'j')
		f->flags |= INTMAX;
	else if (CHAR == 'z')
		f->flags |= SIZE_T;
}

static void	check_capability(FORMAT *f)
{
	if (f->flags & PLUS && f->flags & SPACE)
		f->flags ^= SPACE;
	if (f->flags & ALIGN && f->flags & ZERO)
		f->flags ^= ZERO;
	if (f->flags & PRECISION && f->flags & ZERO && f->prec != 0
		&& CHAR != 'f' && CHAR != 'F')
		f->flags ^= ZERO;
	if (f->width < 0)
	{
		f->width = ABS(f->width);
		f->flags |= ALIGN;
	}
	if ((CHAR == 'f' || CHAR == 'F') && !(f->flags & PRECISION))
		f->prec = 6;
}

void		parse_flags(FORMAT *f)
{
	NEXT;
	while (CHAR)
	{
		if (DIGIT(CHAR))
			parse_digits(f);
		else if (CHAR == ' ' || CHAR == '+')
			f->flags |= (CHAR == '+') ? PLUS : SPACE;
		else if (CHAR == '-' || CHAR == '#')
			f->flags |= (CHAR == '-') ? ALIGN : HASH;
		else if (CHAR == '.')
			parse_precision(f);
		else if (CHAR == '*' && (f->flags |= WIDTH))
			f->width = va_arg(f->list, int);
		else if (CHAR == 'l' || CHAR == 'L' || CHAR == 'h')
			parse_size(f);
		else if (CHAR == 'j' || CHAR == 'z')
			parse_size(f);
		else
			break ;
		NEXT;
	}
	check_capability(f);
}
