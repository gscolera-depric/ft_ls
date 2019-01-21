/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:42:44 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:42:51 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_wchar(FORMAT *f, wchar_t *c)
{
	va_list	copy;

	if (f->flags & DOLLAR)
	{
		va_copy(copy, f->list);
		while (--f->argnum > 0)
			va_arg(copy, void*);
	}
	if (CHAR == 'C' || CHAR == 'c')
		*c = va_arg((f->flags & DOLLAR) ? copy : f->list, wchar_t);
	else
		*c = CHAR;
	if (CHAR == 'c' && !(f->flags & LONG))
		*c = (char)*c;
}

void		manage_char(FORMAT *f)
{
	wchar_t c;

	get_wchar(f, &c);
	f->width -= ft_wchar_len(c);
	if (f->width > 0 && !(f->flags & ALIGN))
		add_values(f, (f->flags & ZERO) ? 48 : 32, f->width);
	add_wchar(f, c);
	if (f->width > 0 && f->flags & ALIGN)
		add_values(f, 32, f->width);
}
