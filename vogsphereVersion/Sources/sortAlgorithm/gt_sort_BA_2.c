/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gt_sort_BA_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:28:19 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 17:33:09 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	exec_rr_s(t_stacks *s, t_move *move)
{
	if (move[0].r == 1 && check_a_swap(s, s->interval))
		--move[0].r;
	check_ab_swap(s, s->interval);
	if (move[0].rr && move[1].rr)
	{
		while (move[0].rr && move[1].rr)
		{
			--move[1].rr;
			--move[0].rr;
			rrr(s);
			if (move[0].r == 1 && check_a_swap(s, s->interval))
				--move[0].r;
			check_ab_swap(s, s->interval);
		}
	}
	return (0);
}

int	exec_r_s(t_stacks *s, t_move *move)
{
	if (move[0].r == 1 && check_a_swap(s, s->interval))
		--move[0].r;
	check_ab_swap(s, s->interval);
	if (move[0].r && move[1].r)
	{
		while (move[0].r && move[1].r)
		{
			--move[1].r;
			--move[0].r;
			rr(s);
			if (move[0].r == 1 && check_a_swap(s, s->interval))
				--move[0].r;
			check_ab_swap(s, s->interval);
		}
	}
	return (0);
}

void	exec_r_rr_norm_de_merde(t_stacks *s, t_move *move)
{
	if (move[0].r)
	{
		--move[0].r;
		ra(s);
	}
	if (move[0].rr)
	{
		rra(s);
		--move[0].rr;
	}
	if (move[1].r)
	{
		rb(s);
		--move[1].r;
	}
	if (move[1].rr)
	{
		rrb(s);
		--move[1].rr;
	}
}

void	exec_r_rr(t_stacks *s, t_move *move)
{
	if (check_a_swap(s, s->interval) && s->l_a->stay && move[0].r == 1)
		--move[0].r;
	if (check_b_swap(s, s->interval) && s->l_b->stay && move[1].r == 1)
		--move[1].r;
	check_ab_swap(s, s->interval);
	while (move[0].r || move[0].rr || move[1].r || move[1].rr)
	{
		exec_r_rr_norm_de_merde(s, move);
		if (check_a_swap(s, s->interval) && s->l_a->stay && move[0].r == 1)
			--move[0].r;
		if (check_b_swap(s, s->interval) && s->l_b->stay && move[1].r == 1)
			--move[1].r;
		check_ab_swap(s, s->interval);
	}
}

void	swap_bf4_push(t_stacks *s)
{
	check_ab_swap(s, s->interval);
	rra(s);
	check_ab_swap(s, s->interval);
	if (s->l_a->prev->stay >= 2)
		rra(s);
	check_ab_swap(s, s->interval);
}
