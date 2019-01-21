/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:52:28 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:52:29 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*get_simple_string(FORMAT *f)
{
	char	*str;
	va_list	copy;

	if (f->flags & DOLLAR)
	{
		va_copy(copy, f->list);
		while (--f->argnum > 0)
			va_arg(copy, void*);
	}
	str = va_arg((f->flags & DOLLAR) ? copy : f->list, char*);
	if (!str)
		str = "(null)";
	return (str);
}

static wchar_t	*get_wide_string(FORMAT *f)
{
	wchar_t	*wstr;
	va_list	copy;

	if (f->flags & DOLLAR)
	{
		va_copy(copy, f->list);
		while (--f->argnum > 0)
			va_arg(copy, void*);
	}
	wstr = va_arg((f->flags & DOLLAR) ? copy : f->list, wchar_t*);
	if (!wstr)
		wstr = L"(null)";
	return (wstr);
}

static int		get_length(FORMAT *f, wchar_t *wstr)
{
	int length;

	length = 0;
	while (*wstr && f->prec > 0)
	{
		if (*wstr < 0X80 && --f->prec >= 0)
			length++;
		else if (*wstr < 0X800 && (f->prec -= 2) >= 0)
			length += 2;
		else if (*wstr < 0X10000 && (f->prec -= 3) >= 0)
			length += 3;
		else if (*wstr < 0X110000 && (f->prec -= 4) >= 0)
			length += 4;
	}
	return (length);
}

static void		manage_wide_string(FORMAT *f)
{
	wchar_t	*wstr;
	int		length;

	wstr = get_wide_string(f);
	length = (f->flags & PRECISION) ? get_length(f, wstr) : ft_wstr_len(wstr);
	f->width -= length;
	if (f->width > 0 && !(f->flags & ALIGN))
		add_values(f, (f->flags & ZERO) ? 48 : 32, f->width);
	while (length > 0)
	{
		if (*wstr < 0X80)
			length--;
		else if (*wstr < 0X800)
			length -= 2;
		else if (*wstr < 0X10000)
			length -= 3;
		else if (*wstr < 0X110000)
			length -= 4;
		add_wchar(f, *(wstr++));
	}
	if (f->width > 0 && f->flags & ALIGN)
		add_values(f, 32, f->width);
}

void			manage_string(FORMAT *f)
{
	char	*str;
	int		length;

	if (CHAR == 'S' || f->flags & LONG)
	{
		manage_wide_string(f);
		return ;
	}
	str = get_simple_string(f);
	length = ft_strlen(str);
	f->prec = (f->flags & PRECISION && f->prec < length) ? f->prec : length;
	length = f->width - f->prec;
	if (length > 0 && !(f->flags & ALIGN))
		add_values(f, (f->flags & ZERO) ? 48 : 32, length);
	while (f->prec--)
		add_char(f, *(str++));
	if (length > 0 && f->flags & ALIGN)
		add_values(f, 32, length);
}
