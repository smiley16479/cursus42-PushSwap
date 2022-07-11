#include "utils.h"

/*
** removes un element, deplaçant la tete de liste & returns it
*/
t_node *remove_node(t_node **l_)
{
	t_node *tmp;

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
t_node *add_node(t_node **l_, t_node *elem)
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
void push(t_node **l_a, t_node **l_b)
{
	add_node(l_b, remove_node(l_a));
}

/*
** pa (push a): Take the first element at the top of b and put it at the top of a.
** Do nothing if b is empty.
*/
void pa(stacks *s)
{
	if (s->sizeB >= 1) {
		// fprintf(stderr, "pa %d\n", s->l_B->data);
		push(&s->l_B, &s->l_A);
		// MAJ maxIdx & minIdx
		if (s->maxIdx < s->l_A->idx)
			s->maxIdx = s->l_A->idx;
		if (s->minIdx > s->l_A->idx)
			s->minIdx = s->l_A->idx;
		++s->sizeA;
		--s->sizeB;
		writeAction(s, e_pa);
	}
	else
		fprintf(stderr, "pa do nothing\n");
}

/*
** pb (push b): Take the first element at the top of a and put it at the top of b. 
** Do nothing if a is empty.
*/
void pb(stacks *s)
{
	if (s->sizeA >= 1) {
		// fprintf(stderr, "pb %d\n", s->l_A->data);
		push(&s->l_A, &s->l_B);
		++s->sizeB;
		--s->sizeA;
		writeAction(s, e_pb);
	}
	else
		fprintf(stderr, "pb do nothing\n");
}