#include "utils.h"

/* 
** sa (swap a): Swap the first 2 elements at the top of stack a.
** Do nothing if there is only one or no elements.
*/
void sa(stacks *s)
{
	int tmp;
	if (s->sizeA < 2)
		return ;
	tmp = *s->tackA;
	*s->tackA = s->tackA[1];
	s->tackA[1] = tmp;
}

/* 
** sb (swap b): Swap the first 2 elements at the top of stack b.
** Do nothing if there is only one or no elements.
*/
void sb(stacks *s)
{
	int tmp;
	if (s->sizeB < 2)
		return ;
	tmp = *s->tackB;
	*s->tackB = s->tackB[1];
	s->tackB[1] = tmp;
}

/*
** ss : sa and sb at the same time.
*/
void ss(stacks *s)
{
	sa(s);
	sb(s);
}

/*
** pa (push a): Take the first element at the top of b and put it at the top of a.
** Do nothing if b is empty.
*/
void pa(stacks *s)
{
	int i;

	if (!s->sizeB)
		return ;
	i = ++s->sizeA;
	while (--i >= 0)
		s->tackA[i + 1] = s->tackA[i];
	*s->tackA = *s->tackB;
	i = -1;
	while (++i < s->sizeB)
		s->tackB[i] = s->tackB[i + 1];
	--s->sizeB;
}


/*
** pb (push b): Take the first element at the top of a and put it at the top of b. 
** Do nothing if a is empty.
*/
void pb(stacks *s)
{
	int i;

	if (!s->sizeA)
		return ;
	i = ++s->sizeB;
	while (--i >= 0)
		s->tackB[i + 1] = s->tackB[i];
	*s->tackB = *s->tackA;
	i = -1;
	while (++i < s->sizeA)
		s->tackA[i] = s->tackA[i + 1];
	--s->sizeA;
}

/*
** ra (rotate a): Shift up all elements of stack a by 1.
** The first element becomes the last one.
*/
void ra(stacks *s)
{
	int i;
	int tmp;

	if (s->sizeA < 2)
		return ;
	tmp = *s->tackA;
	i = -1;
	while (++i < s->sizeA - 1)
		s->tackA[i] = s->tackA[i + 1];
	s->tackA[i] = tmp;
}

/*
** rb (rotate b): Shift up all elements of stack b by 1.
** The first element becomes the last one.
*/
void rb(stacks *s)
{
	int i;
	int tmp;

	if (s->sizeB < 2)
		return ;
	tmp = *s->tackB;
	i = -1;
	while (++i < s->sizeB - 1)
		s->tackB[i] = s->tackB[i + 1];
	s->tackB[i] = tmp;
}

/*
** rr : ra and rb at the same time.
*/
void rr(stacks *s)
{
	ra(s);
	rb(s);
}

/*
** rra (reverse rotate a): Shift down all elements of stack a by 1.
** The last element becomes the first one.
*/
void rra(stacks *s)
{
	int i;
	int tmp;

	if (s->sizeA <2)
		return ;
	tmp = s->tackA[s->sizeA - 1];
	i = s->sizeA;
	while (--i >= 0)
		s->tackA[i + 1] = s->tackA[i];
	*s->tackA = tmp;
}
/*
** rrb (reverse rotate b): Shift down all elements of stack b by 1.
** The last element becomes the first one.
*/
void rrb(stacks *s)
{
	int i;
	int tmp;

	if (s->sizeB <2)
		return ;
	tmp = s->tackB[s->sizeB - 1];
	i = s->sizeB;
	while (--i >= 0)
		s->tackB[i + 1] = s->tackB[i];
	*s->tackB = tmp;
}

/*
** rrr : rra and rrb at the same time.
*/
void rrr(stacks *s)
{
	rra(s);
	rrb(s);
}


/* 
int main()
{
	int tabA[10] = {1,2,3,4,5};
	int tabB[10] = {10,20,30,40,50};
	stacks s;
	s.tackA = tabA;
	s.sizeA = 5;
	s.tackB = tabB;
	s.sizeB = 5;

	for (size_t i = 0; i < s.sizeA; i++)
		printf("%d ", tabA[i]);	
	printf("\n");
	for (size_t i = 0; i < s.sizeB; i++)
		printf("%d ", tabB[i]);
	printf("\n");

	pa(&s);

	for (size_t i = 0; i < s.sizeA; i++)
		printf("%d ", tabA[i]);	
	printf("\n");
	for (size_t i = 0; i < s.sizeB; i++)
		printf("%d ", tabB[i]);
	printf("\n");


	for (size_t i = 0; i < s.sizeA; i++)
		printf("%d ", tabA[i]);	
	printf("\n");
	for (size_t i = 0; i < s.sizeB; i++)
		printf("%d ", tabB[i]);
	printf("\n");


	pb(&s);
	for (size_t i = 0; i < s.sizeA; i++)
		printf("%d ", tabA[i]);	
	printf("\n");
	for (size_t i = 0; i < s.sizeB; i++)
		printf("%d ", tabB[i]);
	printf("\n");
}
*/