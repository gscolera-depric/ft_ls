/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:55:44 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 15:55:58 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_parse_flag(int *flags, char *argv)
{
	while (*(++argv))
	{
		if (*argv == 'l' || *argv == 'a')
			*flags |= (*argv == 'l') ? LS_LONG : LS_ALL;
		else if (*argv == 'R' || *argv == 'r')
			*flags |= (*argv == 'R') ? LS_REC : LS_REV;
		else if (*argv == 't' || *argv == 'u')
			*flags |= (*argv == 't') ? LS_TIME : LS_ACCESS;
		else if (*argv == 'f' || *argv == 'd')
			*flags |= (*argv == 'f') ? LS_NSORT : LS_NOPEN;
		else if (*argv == '1' || *argv == 'S')
			*flags |= (*argv == '1') ? LS_COLUMS : LS_SIZESORT;
		else
			ls_illegal_option_error(*argv);
	}
}

void		ls_parse_args(LS_DIR **dir, char **argv, int *flags)
{
	int i;

	i = 0;
	while (argv[++i])
	{
		if (ft_strequ(argv[i], "--help"))
			ls_show_usage();
		else if (FLAG(argv[i]))
			ls_parse_flag(flags, argv[i]);
	}
	if (*flags & LS_REV)
	{
		while (--i > 0)
			if (!FLAG(argv[i]))
				ls_add_directory(dir, argv[i], flags);
	}
	else
	{
		i = 0;
		while (argv[++i])
			if (!FLAG(argv[i]))
				ls_add_directory(dir, argv[i], flags);
	}
	*flags |= LS_SUBDIR;
}
