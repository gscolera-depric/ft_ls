/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:05:40 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 15:57:32 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_reverse_files(LS_FILE **file)
{
	LS_FILE *prev;
	LS_FILE	*next;
	LS_FILE *current;

	prev = NULL;
	current = *file;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*file = prev;
}

static void	ft_ls(LS_DIR *dir, int *flags)
{
	LS_DIR *subdir;

	subdir = NULL;
	if (*flags & LS_REV)
		ls_reverse_files(&dir->file);
	if (*flags & LS_REC)
		ls_get_subdir_list(dir, &subdir, flags);
	ls_output(dir, flags);
	while (subdir)
	{
		ft_ls(subdir, flags);
		ls_next_directory(&subdir);
	}
}

int			main(int argc, char **argv)
{
	LS_DIR	*dir;
	int		flags;

	dir = NULL;
	flags = 0;
	if (argc > 1)
		ls_parse_args(&dir, argv, &flags);
	if (!dir && !(flags & LS_OPEN_ERROR))
		ls_add_directory(&dir, ".", &flags);
	if (flags & LS_REC || (dir && dir->next))
		flags |= LS_MULTIOUTPUT;
	while (dir)
	{
		ft_ls(dir, &flags);
		ls_next_directory(&dir);
	}
	if (flags & LS_OPEN_ERROR || flags & LS_SUB_ERROR)
		return ((flags & LS_OPEN_ERROR) ? 2 : 1);
	return (0);
}
