#include "utils.h"

int main(int ac, char *av[])
{
	stacks s;
	init(--ac, ++av, &s);
	// if (isSorted(&s)) // si dejà triée ne fait rien
	// 	return (0);
	for (int i = 0; i < s.size; i++)
		printf("%d, ", s.tackSort[i]);
	printf("\n");

	midPointAlgo(&s);
	readAction(&s);
	free(s.tack);
	free(s.action);
	free(s.to_free);
	free(s.tackSort);
	return (0);
}

void init(int ac, char *av[], stacks *s)
{
	if (!ac)
		exit(0);
	s->tackSort = malloc(sizeof(*s->tack) * ac);
	s->tack = malloc(sizeof(*s->tack) * ac);
	s->action = malloc(sizeof(int) * 2500);
	ft_bzero(s->action, sizeof(int)*2500);
	for (size_t i = 0; i < 10; i++)
	{
		printf("%d\n", s->action[i]);
	}
	
	s->l_A = malloc(sizeof(*s->l_A) * ac);
	s->l_B = NULL;

	s->size = 0;
	s->idxAction = 0;
	if (!s->tack || !s->l_A || checkArg(av, s))
		panicERROR();
	sort(s->tackSort, s->size);
	printf("ac : %d, size : %d\n", ac, s->size);

	s->to_free = s->l_A;
	s->size = -1;
	while (++s->size < ac - 1)
	{
		s->l_A[s->size].next = &s->l_A[s->size + 1];
		s->l_A[s->size + 1].prev = &s->l_A[s->size];
	}
	s->l_A[ac - 1].next = &s->l_A[0];
	s->l_A[0].prev = &s->l_A[ac - 1];
	++s->size;
}


/* 
int main(int ac, char *av[])
{
	stacks s;
	init(--ac, ++av, &s);
	// if (isSorted(&s)) // si dejà triée ne fait rien
	// 	return (0);
	for (int i = 0; i < s.size; i++)
		printf("%d\n", s.tackSort[i]);
	printList(s.l_A, s.sizeA);
	printf("\nswap a sizeA %d, sizeB %d\n", s.sizeA, s.sizeB);
	sa(&s);
	// printf("list A\n");
	// printList(s.l_A, s.sizeA);
	// printf("list B\n");
	// printList(s.l_B, s.sizeB);

	printf("\npush a sizeA %d, sizeB %d\n", s.sizeA, s.sizeB);
	pa(&s);

	printf("\npush b sizeA %d, sizeB %d\n", s.sizeA, s.sizeB);
	pb(&s);
	pb(&s);
	pb(&s);

	printf("list A\n");
	printList(s.l_A, s.sizeA);
	printf("list B\n");
	printList(s.l_B, s.sizeB);

	ra(&s);
	rb(&s);
	// printf("\npush b sizeA %d, sizeB %d\n", s.sizeA, s.sizeB);
	// rrr(&s);
	printf("list A\n");
	printList(s.l_A, s.sizeA);
	printf("list B\n");
	printList(s.l_B, s.sizeB);
	free(s.tack);
	free(s.to_free);
	free(s.tackSort);
	return (0);
}
 */