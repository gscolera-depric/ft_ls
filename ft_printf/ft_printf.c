/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 16:14:49 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 16:15:43 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static _Bool	init_format(FORMAT *f)
{
	f->buff_size = 50;
	if (!(f->output = ft_strnew(f->buff_size)))
		return (0);
	f->argnum = 0;
	f->flags = 0;
	f->prec = 0;
	f->width = 0;
	f->length = 0;
	return (1);
}

static void		clean_format(FORMAT *f)
{
	f->argnum = 0;
	f->flags = 0;
	f->prec = 0;
	f->width = 0;
}

static _Bool	manage_text_format(FORMAT *f)
{
	if (compare(f, "{red}"))
		add_string(f, "\033[31m");
	else if (compare(f, "{green}"))
		add_string(f, "\033[32m");
	else if (compare(f, "{yellow}"))
		add_string(f, "\033[33m");
	else if (compare(f, "{blue}"))
		add_string(f, "\033[34m");
	else if (compare(f, "{magenta}"))
		add_string(f, "\033[35m");
	else if (compare(f, "{cyan}"))
		add_string(f, "\033[36m");
	else if (compare(f, "{bold}"))
		add_string(f, "\033[1m");
	else if (compare(f, "{italic}"))
		add_string(f, "\033[3m");
	else if (compare(f, "{underline}"))
		add_string(f, "\033[4m");
	else if (compare(f, "{eoc}"))
		add_string(f, "\033[0m");
	else
		return (0);
	return (1);
}

static void		manage_output(FORMAT *f)
{
	while (CHAR)
	{
		if (CHAR == '{')
		{
			if (!manage_text_format(f))
				add_char(f, CHAR);
		}
		else if (CHAR == '%')
		{
			manage_conversion(f);
			clean_format(f);
		}
		else
			add_char(f, CHAR);
		NEXT;
	}
}

int				ft_printf(const char *format, ...)
{
	FORMAT f;

	if (format[0] == '%' && !format[1])
		return (0);
	if (!(init_format(&f)))
		return (-1);
	f.pos = (char*)format;
	va_start(f.list, format);
	manage_output(&f);
	va_end(f.list);
	if (f.output)
	{
		if (f.length)
			write(1, f.output, f.length);
		free(f.output);
		return (f.length);
	}
	return (-1);
}
