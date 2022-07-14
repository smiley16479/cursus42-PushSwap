/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shared.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:26:33 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 17:34:02 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

/*
** Pop le bon élément de A vers B en checkant si des swap sont
** néccessaire à chaque manip de A
*/
void	pop_ab(t_stacks *s, int idx, int swapInterval)
{
	if (idx == -1)
	{
		printf("pop_ab() idx == -1 (pop_ab non trouvé)\n");
		exit(1);
	}
	if (idx <= s->size_a / 2)
	{
		while (--idx >= 0)
		{
			ra(s);
		}
	}
	else
	{
		while (++idx <= s->size_a)
		{
			rra(s);
		}
	}
	pb(s);
}

static void	sort_simple_3_write_norm2(t_stacks *s, char stack_id, int id)
{
	if (stack_id == 'A' && (id == 1 || id == 4 || id == 5))
		write_action(s, e_sa);
	if (stack_id == 'B' && (id == 1 || id == 4 || id == 5))
		write_action(s, e_sb);
	if (stack_id == 'A' && (id == 2 || id == 5))
		write_action(s, e_ra);
	if (stack_id == 'B' && (id == 2 || id == 5))
		write_action(s, e_rb);
	if (stack_id == 'A' && (id == 3 || id == 4))
		write_action(s, e_rra);
	if (stack_id == 'B' && (id == 3 || id == 4))
		write_action(s, e_rrb);
}

static void	sort_simple_3_write_norm1(int *id, t_node **l, t_node *n[3])
{
	if (*id)
		return ;
	else if (n[0]->data > n[1]->data && n[1]->data > n[2]->data)
	{
		*id = 4;
		swap(*l);
		rev_rotate(l);
	}
	else if (n[0]->data < n[1]->data && n[1]->data > n[2]->data)
	{
		*id = 5;
		swap(*l);
		rotate(l);
	}
}

void	sort_simple_3(t_stacks *s, t_node **l, char stack_id)
{
	t_node	*n[3];
	int		id;

	id = 0;
	n[0] = *l;
	n[1] = (*l)->next;
	n[2] = (*l)->next->next;
	if (n[0]->data > n[1]->data && n[0]->data < n[2]->data)
	{
		id = 1;
		swap(*l);
	}
	else if (n[0]->data > n[1]->data && n[1]->data < n[2]->data)
	{
		id = 2;
		rotate(l);
	}
	else if (n[0]->data < n[1]->data && n[0]->data > n[2]->data)
	{
		id = 3;
		rev_rotate(l);
	}
	sort_simple_3_write_norm1(&id, l, n);
	sort_simple_3_write_norm2(s, stack_id, id);
}

/* 
** Retourne l'index de l'elem ds s->tack_sort
*/
int	get_index(t_stacks *s, int elem)
{
	int	i;

	i = s->size;
	while (i--)
		if (s->tack_sort[i] == elem)
			return (i);
	return (-1);
}
