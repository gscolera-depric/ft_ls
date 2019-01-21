/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_file_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:42:46 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 15:44:27 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	get_size_length(uintmax_t number)
{
	size_t size;

	if (number == 0)
		return (0);
	size = 0;
	while ((number /= 10) > 0)
		size++;
	return (size + 1);
}

static char		ls_get_file_type(mode_t mode)
{
	if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

static void		get_file_access(LS_FILE *file, mode_t mode)
{
	file->access[10] = 0;
	file->access[0] = file->type;
	file->access[1] = (mode & S_IRUSR) ? 'r' : '-';
	file->access[2] = (mode & S_IWUSR) ? 'w' : '-';
	file->access[3] = (mode & S_IXUSR) ? 'x' : '-';
	file->access[4] = (mode & S_IRGRP) ? 'r' : '-';
	file->access[5] = (mode & S_IWGRP) ? 'w' : '-';
	file->access[6] = (mode & S_IXGRP) ? 'x' : '-';
	file->access[7] = (mode & S_IROTH) ? 'r' : '-';
	file->access[8] = (mode & S_IWOTH) ? 'w' : '-';
	file->access[9] = (mode & S_IXOTH) ? 'x' : '-';
}

static void		ls_get_print_params(LS_DIR *dir, LS_FILE *file)
{
	size_t	length;

	length = ft_strlen(file->user);
	if (LS_PP.user < length)
		LS_PP.user = length;
	length = ft_strlen(file->group);
	if (LS_PP.group < length)
		LS_PP.group = length;
	length = get_size_length(file->size);
	if (LS_PP.size < length)
		LS_PP.size = length;
	length = get_size_length(file->links);
	if (LS_PP.links < length)
		LS_PP.links = length;
}

void			ls_get_params(LS_DIR *dir, LS_FILE *file, int *flags)
{
	struct passwd	*uid;
	struct group	*grp;
	struct stat		stat;
	char			*link;

	lstat((file->path) ? file->path : file->name, &stat);
	file->executable = (stat.st_mode & S_IXUSR) ? 1 : 0;
	file->type = ls_get_file_type(stat.st_mode);
	file->time = (*flags & LS_ACCESS) ? stat.st_atime : stat.st_mtime;
	file->size = stat.st_size;
	if (*flags & LS_LONG)
	{
		LS_PP.blocks += stat.st_blocks;
		get_file_access(file, stat.st_mode);
		uid = getpwuid(stat.st_uid);
		grp = getgrgid(stat.st_gid);
		file->links = stat.st_nlink;
		file->user = uid->pw_name;
		file->group = grp->gr_name;
		if (file->type == 'l' && LS_READ_LINK)
			file->link_ptr = link;
		ls_get_print_params(dir, file);
	}
}
