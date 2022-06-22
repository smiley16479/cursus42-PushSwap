#include "utils.h"

void printPTR(stacks *s)
{
	fprintf(stderr, "%30s %20p\n", "s.l_A : ", &(s->l_A));
	fprintf(stderr, "%30s %20p\n", "s.l_A : ", &(s));

	// DS le main
	// fprintf(stderr, "%30s %20p\n","MAIN s.l_A : ", &(s.l_A));
	// fprintf(stderr, "%30s %20p\n","MAIN s.l_A : ", &(s));
	// printPTR(&s);
}

int main(int ac, char *av[])
{
	stacks s;
	init(--ac, ++av, &s);
	// if (isSorted(&s)) // si dejà triée ne fait rien
	// 	return (0);

	// sortSimple_3(&s, &s.l_A, 'A');

	// elem_to_keep_gtSort(&s);
	isBetterAfterSwap(&s);


	// printStacks(s);
	// push_to_B(&s);
	// printStacks(s);

	// midPointAlgo(&s);

	// readAction(&s);
	free(s.action);
	free(s.head_A);
	free(s.tackSort);
	return (0);
}

void init(int ac, char *av[], stacks *s)
{
	if (!ac)
		exit(0);
	s->tackSort = malloc(sizeof(int) * ac);
	s->action = malloc(sizeof(int) * 2500);
	ft_bzero(s->action, sizeof(int)*2500);
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	printf("%d\n", s->action[i]);
	// }
	
	s->l_A = malloc(sizeof(*s->l_A) * ac);
	s->l_B = NULL;

	s->size = 0;
	s->idxAction = 0;
	if (!s->l_A || checkArg(av, s))
		panicERROR();
	sort(s->tackSort, s->size);
	// printf("ac : %d, size : %d\n", ac, s->size);

	s->head_A = s->l_A;
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

