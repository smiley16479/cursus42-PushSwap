/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem2keepSwapFurther.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:57:16 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	the_norm_fucks_up_my_code(t_node *l[4], int interval )
{
	l[2] = l[1]->next;
	l[3] = l[2]->next;
	if (l[1]->idx - l[0]->idx > 0 && l[1]->idx - l[0]->idx <= interval)
	{
		l[1]->stay = e_true;
		l[0] = l[1];
	}
	else if (l[0]->idx - l[1]->idx > 0 && l[0]->idx - l[1]->idx <= 1)
	{
		l[0]->stay = e_swap1;
		l[1]->stay = e_swap2;
	}
	l[1] = l[2];
}

/*
** copie de select_suitSort_pb(t_stacks *s) adapté pour marqué les elem à 
** conserver ds gt_sort ceci est censé amélioré elem_to_keep_gtSort_swap(s)
** Il ne fait que marquer les elem à conserver et ne change rien 
** interval est l'écart en dessous duquel deux valeurs seront gardées
*/
int	*elem_to_keep_gt_sort_swap_further(t_stacks *s, int interval)
{
	int		*tab;
	t_node	*l[4];
	int		i[2];

	tab = malloc(sizeof(int) * s->size_a);
	if (!tab)
		panic_error();
	i[0] = -1;
	while (++i[0] < s->size_a)
	{
		l[1] = s->l_a + i[0];
		l[1]->stay = e_true;
		l[0] = l[1];
		i[1] = 0;
		while (i[1] < s->size_a)
		{
			the_norm_fucks_up_my_code(l, interval);
			++i[1];
		}
		tab[i[0]] = count_n_clear_true(l[1], s->size_a);
	}
	return (tab);
}

void	mark_elem2keep_gt_sort_swap_further(t_stacks *s, int idx, int interval)
{
	t_node	*l[4];
	int		i;

	i = -1;
	count_n_clear_true(s->l_a + idx, s->size_a);
	l[0] = s->l_a + idx;
	l[1] = s->l_a + idx;
	l[1]->stay = e_true;
	while (++i < s->size_a)
	{
		l[2] = l[1]->next;
		l[3] = l[2]->next;
		if (l[1]->idx - l[0]->idx > 0 && l[1]->idx - l[0]->idx <= interval)
		{
			l[1]->stay = e_true;
			l[0] = l[1];
		}
		else if (l[0]->idx - l[1]->idx > 0 && l[0]->idx - l[1]->idx <= 1)
		{
			l[0]->stay = e_swap1;
			l[1]->stay = e_swap2;
		}
		l[1] = l[2];
	}
}

// garde slmt les element != de e_false ds A
// Checkant si des swap sont nécessaire selon: int swapInterval
void	ab_nothin_but_true(t_stacks *s, int trueElem, int swapInterval)
{
	t_node	*l;
	int		i;
	int		idx;

	i = 0;
	s->max_idx = 0;
	s->min_idx = s->size;
	while (i < s->size)
	{
		idx = nearest_popable_true_ab_gt(s);
		if (idx != -1)
			pop_ab(s, idx, swapInterval);
		++i;
	}
	i = -1;
	l = s->l_a;
	while (++i < s->size_a)
	{
		if (s->min_idx > l->idx)
			s->min_idx = l->idx;
		if (s->max_idx < l->idx)
			s->max_idx = l->idx;
		l = l->next;
	}
}

/*
** nearest_popable_true_ab_gt pour SwapFurther où le swap
** est fait en fonction du stay == false
*/
int	nearest_popable_true_ab_gt(t_stacks *s)
{
	int		i;
	int		j;
	t_node	*node[2];

	i = 0;
	j = s->size_a - 1;
	node[0] = s->l_a;
	node[1] = s->l_a->prev;
	while (i <= s->size_a / 2)
	{
		if (node[0]->stay == e_false)
			return (i);
		if (node[1]->stay == e_false)
			return (j);
		node[0] = node[0]->next;
		node[1] = node[1]->prev;
		++i;
		--j;
	}
	return (-1);
}
