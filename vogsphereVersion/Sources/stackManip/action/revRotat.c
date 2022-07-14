/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revRotat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:26:16 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** reverse rotate: Shift down all elements of stack a by 1.
** The last element becomes the first one.
*/
void	rev_rotate(t_node **l_)
{
	if ((*l_))
		(*l_) = (*l_)->prev;
}

/*
** rra (reverse rotate a): Shift down all elements of stack a by 1.
** The last element becomes the first one.
*/
void	rra(t_stacks *s)
{
	if (s->l_a)
	{
		rev_rotate(&s->l_a);
		write_action(s, e_rra);
	}
	else
		printf("cannot perform rra\n");
}

/*
** rrb (reverse rotate b): Shift down all elements of stack b by 1.
** The last element becomes the first one.
*/
void	rrb(t_stacks *s)
{
	if (s->l_b)
	{
		rev_rotate(&s->l_b);
		write_action(s, e_rrb);
	}
	else
		printf("cannot perform rrb\n");
}

/*
** rrr : rra and rrb at the same time.
*/
void	rrr(t_stacks *s)
{
	if (s->l_a && s->l_b)
	{
		write_action(s, e_rrr);
		rev_rotate(&s->l_a);
		rev_rotate(&s->l_b);
	}
	else
		printf("cannot perform rrr\n");
}
