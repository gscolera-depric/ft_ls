/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:41:48 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 16:33:29 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*ls_pathcat(char *home, char *name)
{
	char *path;
	char *start;

	if (!(path = ft_strnew(ft_strlen(home) + ft_strlen(name) + 1)))
		ls_malloc_error();
	start = path;
	while (*home)
		*(path++) = *(home++);
	if (*(path - 1) != '/')
		*(path++) = '/';
	while (*name)
		*(path++) = *(name++);
	return (start);
}

static LS_FILE	*ls_new_file(LS_DIR *dir, char *name)
{
	LS_FILE *new;

	if (!(new = (LS_FILE*)malloc(sizeof(LS_FILE))))
		ls_malloc_error();
	new->name = ft_strdup(name);
	new->path = ls_pathcat(dir->path, new->name);
	new->next = NULL;
	new->prev = NULL;
	new->link_ptr = NULL;
	new->executable = 0;
	return (new);
}

static void		ls_add_without_sort(LS_DIR *dir, LS_FILE *new)
{
	LS_FILE *tmp;

	if (!dir->file)
		dir->file = new;
	else
	{
		tmp = dir->file;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void			ls_next_file(LS_DIR *dir)
{
	LS_FILE *tmp;

	tmp = dir->file;
	dir->file = dir->file->next;
	ft_strdel(&tmp->name);
	if (tmp->path)
		ft_strdel(&tmp->path);
	if (tmp->link_ptr)
		ft_strdel(&tmp->link_ptr);
	free(tmp);
}

void			ls_add_file(LS_DIR *dir, char *name, int *flags)
{
	LS_FILE *new;
	size_t	length;

	if (!(*flags & LS_ALL) && !(*flags & LS_NSORT) && name[0] == '.')
		return ;
	new = ls_new_file(dir, name);
	length = ft_strlen(name);
	LS_PP.count += 1;
	LS_PP.length += length;
	LS_PP.name = (LS_PP.name > length) ? LS_PP.name : length;
	ls_get_params(dir, new, flags);
	if (!dir->file)
		dir->file = new;
	else if (*flags & LS_NSORT)
		ls_add_without_sort(dir, new);
	else
		ls_sort(&dir->file, new, flags);
}
