/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:56:11 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/21 15:57:04 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static _Bool	ls_name_cmp(char *name, char *new)
{
	if (*name == '.')
		name++;
	if (*new == '.')
		new++;
	while (*name && ft_tolower(*name) == ft_tolower(*new))
	{
		name++;
		new++;
	}
	return ((ft_tolower(*new) - ft_tolower(*name) > 0) ? 1 : 0);
}

static void		ls_alphabetic_sort(LS_FILE **file, LS_FILE *new)
{
	LS_FILE *tmp;

	tmp = *file;
	while (tmp->next && ls_name_cmp(tmp->name, new->name))
		tmp = tmp->next;
	if (ls_name_cmp(tmp->name, new->name))
	{
		new->next = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		if (new->next)
			new->next->prev = tmp;
	}
	else
	{
		new->next = tmp;
		new->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = new;
		else
			*file = new;
		tmp->prev = new;
	}
}

static void		ls_time_sort(LS_FILE **file, LS_FILE *new)
{
	LS_FILE *tmp;

	tmp = *file;
	while (tmp->next && tmp->time >= new->time)
		tmp = tmp->next;
	if (tmp->time > new->time)
	{
		new->next = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else if (tmp->time == new->time)
		ls_alphabetic_sort(&tmp, new);
	else
	{
		new->next = tmp;
		new->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = new;
		else
			*file = new;
		tmp->prev = new;
	}
}

static void		ls_size_sort(LS_FILE **file, LS_FILE *new)
{
	LS_FILE *tmp;

	tmp = *file;
	while (tmp->next && tmp->size > new->size)
		tmp = tmp->next;
	if (tmp->size > new->size)
	{
		new->next = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else if (tmp->size == new->size)
		ls_alphabetic_sort(&tmp, new);
	else
	{
		new->next = tmp;
		new->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = new;
		else
			*file = new;
		tmp->prev = new;
	}
}

void			ls_sort(LS_FILE **file, LS_FILE *new, int *flags)
{
	if (*flags & LS_LONG && *flags & LS_ACCESS && *flags & LS_TIME)
		ls_time_sort(file, new);
	else if (*flags & LS_LONG && *flags & LS_ACCESS)
		ls_alphabetic_sort(file, new);
	else if (*flags & LS_ACCESS || *flags & LS_TIME)
		ls_time_sort(file, new);
	else if (*flags & LS_SIZESORT)
		ls_size_sort(file, new);
	else
		ls_alphabetic_sort(file, new);
}
