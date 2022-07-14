/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gt_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:59:00 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** **arr contient le nombre d'élem qui se suivent : par index de l_a[i] modifié
** par l_cpy[0]->data > l_cpy[0]->next->data (le premier *ptr), puis l'idx à
** partir duquel partir ds l_a[i] (le second *ptr) pour avoir le max d'elem qui
** se suivent get_max_followed_elem retourne les index à partir desquel partir
** pour avoir le max d'elem qui se suivent ds la première partie du long
** le premier index ds la seconde le second
*/
long	get_max_followed_elem(int **arr, int size)
{
	int	idx[2];
	int	i;
	int	j;

	idx[0] = 0;
	idx[1] = 0;
	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (++j < size)
		{
			if (arr[idx[0]][idx[1]] < arr[i][j])
			{
				idx[0] = i;
				idx[1] = j;
			}
		}
	}
	return (*((long *) idx));
}

/*
** *arr contient le nombre d'élem qui se suivent par index de l_a[i],
** get_lowest_idx retourne l'index min où le nombre d'élem qui se suivent
** est le plus grand
*/
int	get_lowest_idx(int *arr, int size)
{
	int	index;
	int	i;

	i = -1;
	index = 0;
	while (++i < size)
		if (arr[index] < arr[i])
			index = i;
	return (index);
}

/* 
** Count number of elements greater than each other through
** the stack (a < b < c etc.)
*/
int	followed_elem(t_node *l, int size, t_bool markElem)
{
	int	count_of_followed_elem;
	int	elem;

	if (markElem)
		l->stay = e_true;
	elem = l->data;
	count_of_followed_elem = 1;
	while (size--)
	{
		l = l->next;
		if (elem < l->data && ++count_of_followed_elem)
		{
			if (markElem)
				l->stay = e_true;
			elem = l->data;
		}
	}
	return (count_of_followed_elem);
}

/* 
** int	elem_to_keep_gt_sort(t_stacks *s)
**	{
**		t_node	*l;
**		int		lowest_index;
**		int		*tab;
**		int		i;
**	
**		tab = malloc(s->size * sizeof(int));
**		if (!tab)
**			exit(-1);
**		i = -1;
**		l = s->l_a;
**		while (++i < s->size)
**		{
**			tab[i] = followed_elem(l, s->size, e_false);
**			l = l->next;
**		}
**		lowest_index = get_lowest_idx(tab, s->size);
**		free(tab);
**		return (lowest_index);
**	}
*/

void	gt_sort_swap_further_norm(t_stacks *s, int ***tab, int *inter)
{
	int	idx;

	if (s->size_a / 5)
	{
		*inter = s->size_a / 5;
		idx = *inter;
	}
	else
	{
		*inter = 1;
		idx = 1;
	}
	*tab = malloc(sizeof(int **) * (*inter + 1));
	if (!*tab)
		panic_error();
	ft_bzero(*tab, sizeof(int **) * (*inter + 1));
	while (*inter > 0)
	{
		(*tab)[idx - *inter] = elem_to_keep_gt_sort_swap_further(s, *inter);
		--(*inter);
	}
}

void	gt_sort_swap_further(t_stacks *s)
{
	int		i;
	long	idx;
	int		interval;
	int		**tab;

	if (s->size_a <= 4 && sort_4or_less_nb(s))
		return ;
	gt_sort_swap_further_norm(s, &tab, &interval);
	idx = get_max_followed_elem(tab, s->size_a);
	s->interval = s->size_a / 5 - ((idx << 32) >> 32);
	mark_elem2keep_gt_sort_swap_further(s, (idx >> 32),
		s->size_a / 5 - ((idx << 32) >> 32));
	ab_nothin_but_true(s, tab[((idx << 32) >> 32)][(idx >> 32)],
		s->size_a / 5 - ((idx << 32) >> 32));
	while (s->size_b)
		nearest_inserable_ba_gt(s);
	align(s);
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
