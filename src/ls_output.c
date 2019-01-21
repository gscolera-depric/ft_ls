/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:51:59 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 15:54:09 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_print_file_name(LS_FILE *file, int *flags)
{
	if (file->type == 'd')
		ft_printf("{blue}{bold}%s  {eoc}", file->name);
	else if (file->type == 'l')
		ft_printf("{cyan}{bold}%s  {eoc}", file->name);
	else if (file->executable == 1)
		ft_printf("{green}{bold}%s  {eoc}", file->name);
	else
		ft_printf("%s  ", file->name);
	if (file->type == 'l' && *flags & LS_LONG)
		ft_printf("\b-> %s", file->link_ptr);
	if (*flags & LS_LONG || *flags & LS_COLUMS)
		write(1, "\n", 1);
	*flags |= LS_PRINTED;
}

static int	round(double rows)
{
	return ((rows - (int)rows > 0) ? (int)rows + 1 : (int)rows);
}

static void	ls_print_params(LS_DIR *dir)
{
	char *time;

	time = ctime(&dir->file->time);
	time += 4;
	ft_printf("%s %-*d", dir->file->access, LS_PP.links, dir->file->links);
	ft_printf(" %-*s", LS_PP.user, dir->file->user);
	ft_printf(" %-*s", LS_PP.group, dir->file->group);
	ft_printf(" %-*zu %-.12s ", LS_PP.size, dir->file->size, time);
}

void		ls_output(LS_DIR *dir, int *flags)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	if (*flags & LS_PRINTED)
		write(1, "\n", 1);
	if (*flags & LS_MULTIOUTPUT)
		ft_printf("{magenta}{bold}%s{eoc}:\n", dir->path);
	if (*flags & LS_LONG && dir->file->next)
		ft_printf("total %d\n", LS_PP.blocks);
	else if (LS_PP.name * 2 > w.ws_col)
		*flags |= LS_COLUMS;
	else if (!(*flags & LS_COLUMS) && LS_SCREEN_IS_SMALL)
	{
		ls_print_colums(dir, flags, LS_ROUND);
		return ;
	}
	while (dir->file)
	{
		if (*flags & LS_LONG)
			ls_print_params(dir);
		ls_print_file_name(dir->file, flags);
		ls_next_file(dir);
	}
	if (!(*flags & LS_LONG) && !(*flags & LS_COLUMS))
		write(1, "\n", 1);
}
