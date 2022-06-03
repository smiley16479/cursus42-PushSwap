#include "utils.h"
/*
** swap : Swap the first 2 elements at the top of stack.
** Do nothing if there is only one or no elements.
*/
void swap(t_node **l_, int size)
{
	if (size == 2)
		*l_ = (*l_)->next;
	else if (size > 2)
	{
		size = (*l_)->next->data;
		(*l_)->next->data = (*l_)->data;
		(*l_)->data = size;
	}
}

void sa(stacks *s)
{
	writeAction(s, e_sa);
	swap(&s->l_A, s->sizeA);
}

void sb(stacks *s)
{
	writeAction(s, e_sb);
	swap(&s->l_B, s->sizeB);
}

/*
** ss : sa and sb at the same time.
*/
void ss(stacks *s)
{
	writeAction(s, e_ss);
	swap(&s->l_A, s->sizeA);
	swap(&s->l_B, s->sizeB);
}
