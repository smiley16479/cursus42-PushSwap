#include "utils.h"

/*
** reverse rotate: Shift down all elements of stack a by 1.
** The last element becomes the first one.
*/
void revRotate(t_node **l_)
{
	if ((*l_))
		(*l_) = (*l_)->prev;
}

/*
** rra (reverse rotate a): Shift down all elements of stack a by 1.
** The last element becomes the first one.
*/
void rra(stacks *s)
{
	if (s->l_A)
	{
		revRotate(&s->l_A);
		writeAction(s, e_rra);
	}
	else 
		printf("cannot perform rra\n");
}
/*
** rrb (reverse rotate b): Shift down all elements of stack b by 1.
** The last element becomes the first one.
*/
void rrb(stacks *s)
{
	if (s->l_B)
	{
		revRotate(&s->l_B);
		writeAction(s, e_rrb);
	}
	else 
		printf("cannot perform rrb\n");
}

/*
** rrr : rra and rrb at the same time.
*/
void rrr(stacks *s)
{
	if (s->l_A && s->l_B)
	{
		writeAction(s, e_rrr);
		revRotate(&s->l_A);
		revRotate(&s->l_B);
	}
	else 
		printf("cannot perform rrr\n");
}