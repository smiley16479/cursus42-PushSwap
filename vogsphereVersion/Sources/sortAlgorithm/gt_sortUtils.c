/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gt_sortUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:28:49 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 17:33:33 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	sort_4or_less_nb(t_stacks *s)
{
	s->interval = 1;
	if (s->size_a == 2)
	{
		if (check_a_swap(s, 1))
		{
			sa(s);
			return (1);
		}
	}
	if (s->size == 4)
		pb(s);
	sort_simple_3(s, &s->l_a, 'A');
	if (s->size == 4)
	{
		nearest_inserable_ba_gt(s);
		align(s);
	}
	return (1);
}

static inline int	get0index(t_stacks *s)
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
		if (node[0]->idx == 0)
			return (i);
		if (node[1]->idx == 0)
			return (j);
		node[0] = node[0]->next;
		node[1] = node[1]->prev;
		++i;
		--j;
	}
	return (-1);
}

void	align(t_stacks *s)
{
	int	zero_idx;

	zero_idx = get0index(s);
	if (zero_idx < 0)
		panic_error();
	if (zero_idx < s->size_a / 2)
	{
		while (--zero_idx >= 0)
		{
			check_ab_swap(s, s->interval);
			ra(s);
		}
	}
	else
	{
		while (++zero_idx <= s->size_a)
		{
			check_ab_swap(s, s->interval);
			rra(s);
		}
	}
	check_ab_swap(s, s->interval);
}

void	exec_manip(t_stacks *s, t_move *move)
{
	exec_r_s(s, move);
	exec_rr_s(s, move);
	exec_r_rr(s, move);
	if (s->l_a->prev->stay >= 2)
		swap_bf4_push(s);
	else
		pa(s);
}
