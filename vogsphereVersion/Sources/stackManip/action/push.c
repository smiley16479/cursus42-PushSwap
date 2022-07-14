/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:26:08 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** removes un element, deplaçant la tete de liste & returns it
*/
t_node	*remove_node(t_node **l_)
{
	t_node	*tmp;

	tmp = (*l_);
	if ((*l_) != (*l_)->next)
	{
		(*l_)->next->prev = (*l_)->prev;
		(*l_)->prev->next = (*l_)->next;
		(*l_) = (*l_)->next;
	}
	else
		(*l_) = NULL;
	return (tmp);
}

/* 
** add un element avant l_ & deplace la tete de liste sur cet élement
*/
t_node	*add_node(t_node **l_, t_node *elem)
{
	if ((*l_))
	{
		(*l_)->prev->next = elem;
		elem->prev = (*l_)->prev;
		elem->next = (*l_);
		(*l_)->prev = elem;
	}
	else
	{
		elem->next = elem;
		elem->prev = elem;
	}
	return (*l_ = elem);
}

/*
** push : Take the first element at the top of a and put it at the top of b.
*/
void	push(t_node **l_a, t_node **l_b)
{
	add_node(l_b, remove_node(l_a));
}

/*
** pa (push a): Take the first element at the top of b and put it
** at the top of a. Do nothing if b is empty.
*/
void	pa(t_stacks *s)
{
	if (s->size_b >= 1)
	{
		push(&s->l_b, &s->l_a);
		if (s->max_idx < s->l_a->idx)
			s->max_idx = s->l_a->idx;
		if (s->min_idx > s->l_a->idx)
			s->min_idx = s->l_a->idx;
		++s->size_a;
		--s->size_b;
		write_action(s, e_pa);
	}
	else
		fprintf(stderr, "pa do nothing\n");
}

/*
** pb (push b): Take the first element at the top of a and put it
** at the top of b. Do nothing if a is empty.
*/
void	pb(t_stacks *s)
{
	if (s->size_a >= 1)
	{
		push(&s->l_a, &s->l_b);
		++s->size_b;
		--s->size_a;
		write_action(s, e_pb);
	}
	else
		fprintf(stderr, "pb do nothing\n");
}
