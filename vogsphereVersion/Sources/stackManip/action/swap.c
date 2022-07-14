/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:26:21 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
/*
** swap : Swap the first 2 elements at the top of stack.
** Do nothing if there is only one or no elements.
*/
void	swap(t_node *l_)
{
	int	tmp;

	if (l_ && l_->next)
	{
		tmp = l_->next->data;
		l_->next->data = l_->data;
		l_->data = tmp;
		tmp = l_->next->idx;
		l_->next->idx = l_->idx;
		l_->idx = tmp;
		l_->next->stay = 1;
		l_->stay = 1;
	}
}

void	sa(t_stacks *s)
{
	write_action(s, e_sa);
	swap(s->l_a);
}

void	sb(t_stacks *s)
{
	write_action(s, e_sb);
	swap(s->l_b);
}

/*
** ss : sa and sb at the same time.
*/
void	ss(t_stacks *s)
{
	write_action(s, e_ss);
	swap(s->l_a);
	swap(s->l_b);
}
