#include "utils.h"
/*
** rotate : Shift up all elements of stack a by 1.
** The first element becomes the last one.
*/
void rotate(t_node **l_)
{
	if ((*l_))
		(*l_) = (*l_)->next;
}

/*
** ra (rotate a): Shift up all elements of stack a by 1.
** The first element becomes the last one.
*/
void ra(stacks *s)
{
	if (s->l_A)
	{
		fprintf(stderr, "ra %d\n", s->l_A->data);
		rotate(&s->l_A);
		writeAction(s, e_ra);
	}
	else 
		printf("cannot perform ra\n");
}

/*
** rb (rotate b): Shift up all elements of stack b by 1.
** The first element becomes the last one.
*/
void rb(stacks *s)
{
	if (s->l_B)
	{
		fprintf(stderr, "rb %d\n", s->l_B->data);
		rotate(&s->l_B);
		writeAction(s, e_rb);
	}
	else 
		printf("cannot perform rb\n");
}

/*
** rr : ra and rb at the same time.
*/
void rr(stacks *s)
{
	if (s->l_B && s->l_A)
	{
		fprintf(stderr, "rr %d, %d\n", s->l_A->data, s->l_B->data);
		writeAction(s, e_rr);
		rotate(&s->l_A);
		rotate(&s->l_B);
	}
	else 
		printf("cannot perform rr\n");
}