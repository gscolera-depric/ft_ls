/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_colums_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:45:34 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 15:39:23 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_free_list(LS_DIR *dir)
{
	LS_FILE *tmp;

	while (dir->file)
	{
		tmp = dir->file;
		dir->file = dir->file->next;
		ft_strdel(&tmp->name);
		if (tmp->path)
			ft_strdel(&tmp->path);
		if (tmp->link_ptr)
			ft_strdel(&tmp->link_ptr);
		free(tmp);
	}
}

static void	ls_print_file_name(LS_DIR *dir, LS_FILE *file, int *flags)
{
	if (file->type == 'd')
		ft_printf("{blue}{bold}%-*s{eoc}", LS_PP.name, file->name);
	else if (file->type == 'l')
		ft_printf("{cyan}{bold}%-*s{eoc}", LS_PP.name, file->name);
	else if (file->executable == 1)
		ft_printf("{green}{bold}%-*s{eoc}", LS_PP.name, file->name);
	else
		ft_printf("%-*s", LS_PP.name, file->name);
	*flags |= LS_PRINTED;
}

void		ls_print_colums(LS_DIR *dir, int *flags, short rows)
{
	LS_FILE	*current;
	LS_FILE *start;
	short	colum;
	short	curent_row;

	curent_row = rows;
	start = dir->file;
	while (curent_row-- > 0)
	{
		current = start;
		ls_print_file_name(dir, current, flags);
		while (current)
		{
			colum = rows;
			while (colum-- > 0 && current)
				current = current->next;
			if (current)
				ls_print_file_name(dir, current, flags);
		}
		write(1, "\n", 1);
		start = start->next;
	}
	ls_free_list(dir);
}
