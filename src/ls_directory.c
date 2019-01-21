/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:39:41 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 16:32:44 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static _Bool	ls_parse_directory(LS_DIR *dir, int *flags)
{
	struct dirent	*sd;
	struct stat		stat;

	if (!(dir->ptr = opendir(dir->path)) && lstat(dir->path, &stat) == -1)
		return (ls_open_error(dir->path, flags));
	if (dir->ptr && !(*flags & LS_NOPEN))
	{
		while ((sd = readdir(dir->ptr)))
			ls_add_file(dir, sd->d_name, flags);
	}
	else
	{
		if (!(dir->file = (LS_FILE*)malloc(sizeof(LS_FILE))))
			ls_malloc_error();
		dir->file->name = ft_strdup(dir->path);
		dir->file->path = NULL;
		dir->file->next = NULL;
		dir->file->prev = NULL;
		dir->file->link_ptr = NULL;
		dir->print_params.count = 1;
		dir->print_params.name = ft_strlen(dir->path);
		dir->print_params.length = dir->print_params.name;
		ls_get_params(dir, dir->file, flags);
	}
	return (1);
}

static LS_DIR	*ls_new_dir(LS_DIR *new, char *dirname)
{
	if (!(new = (LS_DIR*)malloc(sizeof(LS_DIR))))
		ls_malloc_error();
	new->path = ft_strdup(dirname);
	new->file = NULL;
	new->next = NULL;
	new->print_params.user = 0;
	new->print_params.group = 0;
	new->print_params.size = 0;
	new->print_params.links = 0;
	new->print_params.name = 0;
	new->print_params.count = 0;
	new->print_params.blocks = 0;
	new->print_params.length = 0;
	return (new);
}

void			ls_next_directory(LS_DIR **dir)
{
	LS_DIR *tmp;

	tmp = *dir;
	*dir = (*dir)->next;
	if (tmp->path)
		ft_strdel(&tmp->path);
	if (tmp->ptr)
		closedir(tmp->ptr);
	free(tmp);
}

void			ls_get_subdir_list(LS_DIR *dir, LS_DIR **subdir, int *flags)
{
	LS_FILE *tmp;

	*flags |= LS_SUBDIR;
	tmp = dir->file;
	while (tmp)
	{
		if (tmp->type == 'd')
			ls_add_directory(subdir, tmp->path, flags);
		tmp = tmp->next;
	}
}

void			ls_add_directory(LS_DIR **dir, char *dirname, int *flags)
{
	LS_DIR *new;
	LS_DIR *tmp;

	new = NULL;
	new = ls_new_dir(new, dirname);
	if (!ls_parse_directory(new, flags))
	{
		ft_strdel(&new->path);
		free(new);
		return ;
	}
	if (!*dir)
		*dir = new;
	else
	{
		tmp = *dir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
