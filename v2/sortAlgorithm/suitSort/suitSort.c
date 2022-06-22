#include "utils.h"

/* 
** Garde ds la stack A les élements qui se suivent (1, 2),
** Ou qui se suivent avec un intrut entre (1, 42, 2)
** Ou qui se suivent ds le mauvais ordre (2, 1) || (2, 42, 1) ils seront swapés par la suite
*/

// Compliqué ...
void select_suitSort_pb(stacks *s)
{
	t_node *l = s->l_A;
	int i[4] = {0};

	while (i[0] < s->sizeA)
	{
		i[1] = get_index(s, l->data);
		i[2] = get_index(s, l->next->data);
		i[3] = get_index(s, l->next->next->data);
		fprintf(stderr, "%3d, %3d, %3d, %8d\n", l->data, l->next->data, l->next->next->data, i[0]);
		// fprintf(stderr, "%3d, %3d, %3d\n", i[1], i[2], i[3]);
		if ((i[1] - i[2] == - 1 || i[1] - i[2] == 1) && fprintf(stderr, "True (i : %d)\n\n", i[0]))
		{
			l->stay = e_true;
			l->next->stay = e_true;
		}
		else if (i[1] - i[3] == - 1 || i[1] - i[3] == 1)
		{
			l->stay = e_true;
			l->next->stay = e_false;
			l->next->next->stay = e_true;
			l = l->next;
			++i[0];
			fprintf(stderr, "True False True (i : %d)\n\n", i[0]);
		}
		else if (i[0] < s->sizeA - 1)
		{
			if (!l->stay)
				l->stay = e_false;
			// l->next->stay = e_false;
			// l = l->next;
			// ++i[0];
			fprintf(stderr, "False (i : %d)\n\n", i[0]);
		}
		l = l->next;
		++i[0];
	}
}

void push_to_B(stacks *s)
{
	int i;

	select_suitSort_pb(s);
	i = -1;
	while (++i < s->size)
	{
		if (check_A_Swap(s))
		{
			s->l_A->stay = e_true;
			s->l_A->next->stay = e_true;
			sa(s);
			select_suitSort_pb(s);
		}
		if (!s->l_A->stay)
			pb(s);
		else
			ra(s);
	}
}

