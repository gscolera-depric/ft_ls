/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:04:28 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 16:01:09 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdlib.h>
# include <stdio.h>

# define FORMAT t_format
# define FORMAT t_format
# define CHAR *(f->pos)
# define NEXT f->pos++
# define PREVIOUS f->pos--
# define N_CHAR *(f->pos + 1)
# define P_CHAR *(f->pos - 1)
# define ABS(x) (x < 0) ? -x : x
# define DIGIT(x) (x > 47 && x < 58) ? 1 : 0
# define MALLOC_ERROR "Memory allocation error!"

/*
***************BITMASKS*****************************
*/
# define ZERO (1 << 0)
# define PLUS (1 << 1)
# define MINUS (1 << 2)
# define SPACE (1 << 3)
# define ALIGN (1 << 4)
# define HASH (1 << 5)
# define DOLLAR (1 << 6)
# define WIDTH (1 << 7)
# define PRECISION (1 << 8)
# define LONG (1 << 9)
# define LONG1 (1 << 10)
# define LONG2 (1 << 11)
# define SHORT (1 << 12)
# define SHORT1 (1 << 13)
# define INTMAX (1 << 14)
# define SIZE_T (1 << 15)
# define PREFFIX (1 << 16)

/*
***************WCHAR*****************************
*/
# define WCHAR21 ((c >> 6) | 0xC0)
# define WCHAR22 ((c & 0x3F) | 0x80)
# define WCHAR31 ((c >> 12) | 0xE0)
# define WCHAR32 (((c >> 6) & 0x3F) | 0x80)
# define WCHAR33 ((c & 0X3F) | 0x80)
# define WCHAR41 ((c >> 18) | 0xF0)
# define WCHAR42 (((c >> 12) & 0x3F) | 0x80)
# define WCHAR43 (((c >> 6) & 0x3F) | 0x80)
# define WCHAR44 ((c & 0x3F) | 0x80)

# ifdef __linux__
#  typedef intmax_t __intmax_t
#  typedef uintmax_t __uintmax_t
# endif

typedef struct	s_format
{
	short	argnum;
	int		flags;
	int		prec;
	int		width;
	int		length;
	size_t	buff_size;
	char	*pos;
	char	*output;
	va_list	list;
}				t_format;

int				ft_printf(const char *format, ...);

/*
***************MANAGES*********************************
*/
void			manage_conversion(FORMAT *f);
void			manage_char(FORMAT *f);
void			manage_string(FORMAT *f);
void			manage_adress(FORMAT *f);
void			manage_decimal(FORMAT *f);
void			manage_unsigned(FORMAT *f);
void			manage_octal(FORMAT *f);
void			manage_hex(FORMAT *f);
void			manage_double(FORMAT *f);
void			manage_bits(FORMAT *f);
/*
***************LIBFT***********************************
*/
char			*ft_strnew(size_t size);
int				ft_strlen(const char *str);
int				ft_wchar_len(wchar_t c);
int				ft_wstr_len(wchar_t *wstr);
char			*ft_strdup(const char *str);
char			*ft_strjoin(const char *s1, const char *s2);
_Bool			ft_strequ(const char *str1, const char *str2);
char			ft_tolower(char c);
size_t			ft_numlen(int nbr);
void			ft_strdel(char **str);
/*
***************OUTPUT***********************************
*/
void			add_char(FORMAT *f, char c);
void			add_string(FORMAT *f, char *str);
void			add_wchar(FORMAT *f, wchar_t c);
void			add_sign(FORMAT *f);
/*
***************TOOLS***********************************
*/
_Bool			compare(FORMAT *f, char *text_format);
void			parse_flags(FORMAT *f);
void			add_values(FORMAT *f, char value, int size);
void			ld_to_ascii(FORMAT *f, long double value, size_t size,
	char *str);

#endif
