/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoSwapCheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:26:27 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* 
** Check si un swap est possible sur la/les stack/s
** pour un swap strict, spécifier un interval de 1.
*/
inline int	check_a_swap(t_stacks *s, int interval)
{
	if (s->size_a >= 2 && s->l_a->idx > s->l_a->next->idx
		&& s->l_a->idx - s->l_a->next->idx <= interval)
	{
		return (1);
	}
	return (0);
}

inline int	check_b_swap(t_stacks *s, int interval)
{
	if (s->size_b >= 2 && s->l_b->idx < s->l_b->next->idx
		&& s->l_b->next->idx - s->l_b->idx <= interval)
		return (1);
	return (0);
}

int	check_ab_swap(t_stacks *s, int interval)
{
	int	a;
	int	b;

	if (s->size_a >= 2 && s->l_a->stay)
		a = check_a_swap(s, interval);
	else
		a = e_false;
	if (s->size_b >= 2 && s->l_b->stay)
		b = check_b_swap(s, interval);
	else
		b = e_false;
	if (a || b)
	{
		if (a && b)
			ss(s);
		else if (a)
			sa(s);
		else if (b)
			sb(s);
		return (1);
	}
	return (0);
}
