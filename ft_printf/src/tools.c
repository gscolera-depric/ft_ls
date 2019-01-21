/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 16:13:48 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 16:13:52 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

_Bool		compare(FORMAT *f, char *text_format)
{
	char i;

	i = 0;
	while (*(f->pos + i) && *text_format)
		if (*(f->pos + i++) != *(text_format++))
			return (0);
	f->pos += i - 1;
	return (1);
}

void		add_values(FORMAT *f, char value, int size)
{
	while (size-- > 0)
		add_char(f, value);
}
