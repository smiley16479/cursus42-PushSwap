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

	// elem_to_keep_gtSort(&s);
	gtSort_Family_Algorithm(&s);


	// printStacks(s);

	readAction(&s);
	free(s.action);
	free(s.head_A);
	free(s.tackSort);
	return (0);
}
