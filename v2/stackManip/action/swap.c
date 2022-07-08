#include "utils.h"
/*
** swap : Swap the first 2 elements at the top of stack.
** Do nothing if there is only one or no elements.
*/
void swap(t_node *l_)
{
	int tmp;
	if (l_ && l_->next)
	{
		tmp = l_->next->data;
		l_->next->data = l_->data;
		l_->data = tmp;
		tmp = l_->next->idx;
		l_->next->idx = l_->idx;
		l_->idx = tmp;
// Est-ce que ça ne devrait pas plutot virer le statut "stay"
		// tmp = l_->next->stay = 0;
		l_->next->stay = l_->stay = 1;
		// l_->stay = tmp;
	}
}

void sa(stacks *s)
{
	fprintf(stderr, "sa %d & %d\n", s->l_A->data, s->l_A->next->data);
	writeAction(s, e_sa);
	swap(s->l_A);
}

void sb(stacks *s)
{
	fprintf(stderr, "sb %d & %d\n", s->l_B->data, s->l_B->next->data);
	writeAction(s, e_sb);
	swap(s->l_B);
}

/*
** ss : sa and sb at the same time.
*/
void ss(stacks *s)
{
	writeAction(s, e_ss);
	swap(s->l_A);
	swap(s->l_B);
}
