/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:26:36 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
/*
** void printList(t_node *l, int size)
** {
** 	for (size_t i = 0; i < size; i++) {
** 		fprintf(stderr, "prev : %p -> me(%2d) stat %d : %p -> next : %p\n",
			l->prev, l->data, l->stay, l, l->next);
** 		// printf("data : %d\n", l[i].data);
** 		l = l->next;
** 	}
** }
** 
** void printStacks(t_stacks s)
** {
** 	fprintf(stderr, "list A\n");
** 	printList(s.l_a, s.size_a);
** 	fprintf(stderr, "list B\n");
** 	printList(s.l_b, s.size_b);
** }
*/

void	write_action(t_stacks *s, enum e_action act)
{
	if (!(s->action[s->idx_action] & 0x0F))
	{
		(s->action[s->idx_action]) = act;
	}
	else if (!(s->action[s->idx_action] & 0xF0))
	{
		s->action[s->idx_action] |= (act << 4);
		++s->idx_action;
	}
}

void	initialize_action_array(char *a[12])
{
	a[0] = "";
	a[1] = "sa\n";
	a[2] = "sb" ;
	a[3] = "ss\n";
	a[4] = "pa\n";
	a[5] = "pb\n";
	a[6] = "ra\n";
	a[7] = "rb\n";
	a[8] = "rr\n";
	a[9] = "rra\n";
	a[10] = "rrb\n";
	a[11] = "rrr\n";
}

void	read_action(t_stacks *s)
{
	int		i;
	int		j;
	char	*a[12];

	initialize_action_array(a);
	i = -1;
	while (++i <= s->idx_action && s->action[i])
	{
		j = 0;
		while (++j <= e_rrr)
		{
			if ((s->action[i] & 0x0F) == j)
			{
				write(1, a[j], ft_strlen(a[j]));
			}
		}
		j = 0;
		while (++j <= e_rrr)
		{
			if (((s->action[i] & 0xF0) >> 4) == j)
			{
				write(1, a[j], ft_strlen(a[j]));
			}
		}
	}
}

int	count_n_clear_true(t_node *l, int size)
{
	int	i;

	i = 0;
	while (size--)
	{
		if (l->stay && ++i)
			l->stay = e_false;
		l = l->next;
	}
	return (i);
}

t_node	*ft_lst_cpy(t_node *l, size_t n)
{
	t_node	*to_ret;
	size_t	i;

	to_ret = malloc(n * sizeof(t_node));
	if (!to_ret)
		exit(-1);
	to_ret[n - 1].next = &(to_ret[0]);
	to_ret[0].prev = &(to_ret[n - 1]);
	i = -1;
	while (++i < n)
	{
		to_ret[i].stay = l->stay;
		to_ret[i].data = l->data;
		to_ret[i].idx = l->idx;
		if (i != n - 1)
			to_ret[i].next = &(to_ret[i + 1]);
		if (i != 0)
			to_ret[i].prev = &(to_ret[i - 1]);
		l = l->next;
	}
	return (to_ret);
}
