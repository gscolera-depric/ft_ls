/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:43:10 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:43:14 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	manage_conversion(FORMAT *f)
{
	parse_flags(f);
	if (CHAR == 'S' || CHAR == 's')
		manage_string(f);
	else if (CHAR == 'd' || CHAR == 'D' || CHAR == 'i')
		manage_decimal(f);
	else if (CHAR == 'p')
		manage_adress(f);
	else if (CHAR == 'u' || CHAR == 'U')
		manage_unsigned(f);
	else if (CHAR == 'o' || CHAR == 'O')
		manage_octal(f);
	else if (CHAR == 'x' || CHAR == 'X')
		manage_hex(f);
	else if (CHAR == 'f' || CHAR == 'F')
		manage_double(f);
	else if (CHAR == 'b')
		manage_bits(f);
	else
		manage_char(f);
}
