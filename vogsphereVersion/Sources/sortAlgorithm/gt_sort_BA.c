/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gt_sort_BA.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:28:19 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** Ajoute (ou soustrait (rr)) les move requis par stack A et B
*/
int	calcul_added_move(t_stacks *s, t_move *move)
{
	if (move[1].r && move[0].r)
	{
		if (move[1].r > move[0].r)
			return (move[1].r);
		else
			return (move[0].r);
	}
	else if (move[1].rr && move[0].rr)
	{
		if (move[1].rr > move[0].rr)
			return (move[1].rr);
		else
			return (move[0].rr);
	}
	else
	{
		return (move[0].r + move[0].rr + move[1].r + move[1].rr);
	}
}

static inline int	is_between(t_node *l_a, int idx)
{
	if (l_a->prev->idx < idx && idx < l_a->idx)
		return (1);
	return (0);
}

void	calcul_a_move(t_stacks *s, t_move *move, t_node *l_b)
{
	int		i;
	t_node	*l_a;

	i = 0;
	l_a = s->l_a;
	while (!is_between(l_a, l_b->idx) && i < s->size_a)
	{
		l_a = l_a->next;
		++i;
	}
	if (!is_between(l_a, l_b->idx) && i == s->size_a)
	{
		i = -1;
		while (++i < s->size_a)
		{
			if (l_a->idx == s->min_idx)
				break ;
			else
				l_a = l_a->next;
		}
	}
	if (i <= s->size_a / 2)
		move->r = i;
	else
		move->rr = s->size_a - i;
}

/*
** *arr contient le nombre de mouvement à effectuer par index de l_b[i],
** getLowestValue retourne l'index min où le nombre de mouvement à effectuer
** est le plus petit
*/
int	get_lowest_value_idx(t_moves *arr, int size)
{
	int	index;
	int	i;

	i = 0;
	index = 0;
	while (++i < size)
		if (arr[i].added_move < arr[index].added_move)
			index = i;
	return (index);
}

int	nearest_inserable_ba_gt(t_stacks *s)
{
	int		i;
	t_node	*l_b;
	t_moves	*tab;

	tab = malloc(sizeof(*tab) * s->size_b);
	if (!tab)
		panic_error();
	ft_bzero(tab, sizeof(*tab) * s->size_b);
	i = -1;
	l_b = s->l_b;
	while (++i < s->size_b)
	{
		if (i <= s->size_b / 2)
			tab[i].move[1].r = i;
		else
			tab[i].move[1].rr = s->size_b - i;
		calcul_a_move(s, tab[i].move, l_b);
		tab[i].added_move = calcul_added_move(s, tab[i].move);
		l_b = l_b->next;
	}
	i = get_lowest_value_idx(tab, s->size_b);
	exec_manip(s, tab[i].move);
	free(tab);
	return (0);
}
