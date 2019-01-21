/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:05:32 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 15:58:05 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include "../ft_printf/includes/ft_printf.h"

/*
******************LS_FLAGS*****************************************
*/
# define LS_ALL 		(1 << 1)
# define LS_REC 		(1 << 2)
# define LS_REV 		(1 << 3)
# define LS_NSORT 		(1 << 4)
# define LS_NOPEN 		(1 << 5)
# define LS_COLUMS 		(1 << 6)
# define LS_MULTIOUTPUT (1 << 7)
# define LS_SUBDIR		(1 << 8)
# define LS_OPEN_ERROR 	(1 << 9)
# define LS_SUB_ERROR	(1 << 10)
# define LS_PRINTED		(1 << 11)
# define LS_SIZESORT 	(1 << 12)
# define LS_TIME 		(1 << 13)
# define LS_ACCESS 		(1 << 14)
# define LS_LONG 		(1 << 15)

/*
******************LS_STRUCTS*****************************************
*/
# define LS_DIR				t_lsdir
# define LS_FILE 			t_lsfile
# define LS_COL				t_lscol
# define LS_PRINT_PARAMS 	t_lsprintparams

/*
*******************OTHER**********************************************
*/
# define FLAG(argv) 		(argv[0] == 45 && argv[1]) ? 1 : 0
# define LS_PP				dir->print_params
# define LS_SCREEN_IS_SMALL	w.ws_col < LS_PP.length + (LS_PP.count - 1) * 2
# define LS_READ_LINK		readlink(file->path, (link = ft_strnew(255)), 255)
# define LS_ROUND	round((double)(++LS_PP.name + 2) * LS_PP.count / w.ws_col)

typedef	struct	s_lsfile
{
	char				*path;
	char				*name;
	char				*user;
	char				*group;
	char				*link_ptr;
	time_t				time;
	char				type;
	uintmax_t			size;
	nlink_t				links;
	char				access[12];
	_Bool				executable;
	struct s_lsfile		*prev;
	struct s_lsfile		*next;
	struct s_lsfile		*next_in_colum;
}				t_lsfile;

typedef struct	s_lsprintparams
{
	size_t				length;
	size_t				user;
	size_t				group;
	size_t				size;
	size_t				links;
	size_t				name;
	size_t				count;
	blkcnt_t			blocks;
}				t_lsprintparams;

typedef	struct	s_lsdir
{
	char				*path;
	DIR					*ptr;
	LS_FILE				*file;
	LS_PRINT_PARAMS		print_params;
	struct s_lsdir		*next;
}				t_lsdir;

void			ls_parse_args(LS_DIR **dir, char **argv, int *flag);
void			ls_print_colums(LS_DIR *dir, int *flags, short rows);
void			ls_output(LS_DIR *dir, int *flags);
/*
**************LS_DIRECTORY**********************************************
*/
void			ls_add_directory(LS_DIR **dir, char *dirname, int *flags);
void			ls_next_directory(LS_DIR **dir);
void			ls_get_subdir_list(LS_DIR *dir, LS_DIR **subdir, int *flags);

/*
***************LS_FILE**************************************************
*/
void			ls_add_file(LS_DIR *dir, char *name, int *flags);
void			ls_get_params(LS_DIR *dir, LS_FILE *file, int *flag);
void			ls_next_file(LS_DIR *dir);
/*
***************LS_SORT***************************************************
*/
void			ls_sort(LS_FILE **file, LS_FILE *new, int *flags);
/*
***************ERRORS****************************************************
*/
void			ls_show_usage();
void			ls_malloc_error();
void			ls_illegal_option_error(char c);
_Bool			ls_open_error(char *path, int *flags);
#endif
