/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:26:18 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
/*
** rotate : Shift up all elements of stack a by 1.
** The first element becomes the last one.
*/
void	rotate(t_node **l_)
{
	if ((*l_))
		(*l_) = (*l_)->next;
}

/*
** ra (rotate a): Shift up all elements of stack a by 1.
** The first element becomes the last one.
*/
void	ra(t_stacks *s)
{
	if (s->l_a)
	{
		rotate(&s->l_a);
		write_action(s, e_ra);
	}
	else
		printf("cannot perform ra\n");
}

/*
** rb (rotate b): Shift up all elements of stack b by 1.
** The first element becomes the last one.
*/
void	rb(t_stacks *s)
{
	if (s->l_b)
	{
		rotate(&s->l_b);
		write_action(s, e_rb);
	}
	else
		printf("cannot perform rb\n");
}

/*
** rr : ra and rb at the same time.
*/
void	rr(t_stacks *s)
{
	if (s->l_b && s->l_a)
	{
		write_action(s, e_rr);
		rotate(&s->l_a);
		rotate(&s->l_b);
	}
	else
		printf("cannot perform rr\n");
}
