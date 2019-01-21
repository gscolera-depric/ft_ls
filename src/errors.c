/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:59:18 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 15:59:19 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_malloc_error(void)
{
	ft_printf("{red}{bold}ft_ls error: {eoc}memory allocation failed!\n");
	exit(3);
}

void		ls_show_usage(void)
{
	ft_printf("=========================================================\n");
	ft_printf("{blue}{bold}Usage: {red}./ft_ls{eoc} [OPTION] [FILE]\n");
	ft_printf("\nAvailible options:\n\n");
	ft_printf("{cyan}%-5s{eoc} do not ignore entries starting with .;\n", "-a");
	ft_printf("{cyan}%-5s{eoc} use a long listing format;\n", "-l");
	ft_printf("{cyan}%-5s{eoc} list subdirectories recursively;\n", "-R");
	ft_printf("{cyan}%-5s{eoc} reverse order while sorting;\n", "-r");
	ft_printf("{cyan}%-5s{eoc} sort by modification time;\n", "-t");
	ft_printf("{cyan}%-5s{eoc} with -lt: sort, show, by access time;\n", "-u");
	ft_printf("%-5s with -l: show access time and sort by name;\n", " ");
	ft_printf("%-5s otherwise: sort by access time, newest first;\n", " ");
	ft_printf("{cyan}%-5s{eoc} do not sort;\n", "-f");
	ft_printf("{cyan}%-5s{eoc} list directories themselves\n", "-d");
	ft_printf("{cyan}%-5s{eoc} list one file per line;\n", "-1");
	ft_printf("{cyan}%-5s{eoc} sort by file size, largest first;\n", "-S");
	ft_printf("\nReturn values:\n\n");
	ft_printf("{green}{bold} 0{eoc} if OK,\n");
	ft_printf("{yellow}{bold} 1{eoc} if minor problems ,\n");
	ft_printf("{red}{bold} 2{eoc} if major problems.\n");
	ft_printf("{red}{bold} 3{eoc} if malloc error.\n");
	ft_printf("=========================================================\n");
	exit(0);
}

void		ls_illegal_option_error(char c)
{
	ft_printf("{red}{bold}ft_ls error:{eoc} illegal option '%c'!\n", c);
	ft_printf("Try 'ft_ls --help' for more information.\n");
	exit(2);
}

_Bool		ls_open_error(char *path, int *flags)
{
	*flags |= (*flags & LS_SUBDIR) ? LS_SUB_ERROR : LS_OPEN_ERROR;
	ft_printf("{red}{bold}ft_ls error:{eoc} ");
	perror(path);
	*flags |= LS_PRINTED;
	return (0);
}
