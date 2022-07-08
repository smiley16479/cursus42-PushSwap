#include "utils.h"


int sort_3orLessNb(stacks *s)
{
	if (s->sizeA == 2)
		if (check_A_Swap(s,1))
			sa(s);
	sortSimple_3(s, &s->l_A, 'A');
	return 1;
}

inline void isInInterval_l0l1(t_node **l, int *i, int interval)
{
	if (l[1]->idx - l[0]->idx > 0 && l[1]->idx - l[0]->idx <= interval)
	{
		l[1]->stay = e_true;
		l[0] = l[1];
	}
	// ds le désordre
	else if (l[0]->idx - l[1]->idx > 0 && l[0]->idx - l[1]->idx <= interval)
	{
		
	}
}

static inline int get0index(stacks *s)
{
	int i;
	int j;
	t_node *node[2];

	i = 0;
	j = s->sizeA - 1;
	node[0] = s->l_A;
	node[1] = s->l_A->prev;
	while (i <= s->sizeA / 2)
	{
		if (node[0]->idx == 0)
			return i;
		if (node[1]->idx == 0)
			return j;
		node[0] = node[0]->next;
		node[1] = node[1]->prev;
		++i;
		--j;
	}
	return -1;
}

void align(stacks *s)
{
	int zeroIdx;

	if ((zeroIdx = get0index(s)) < 0)
		panicERROR();
	if (zeroIdx < s->sizeA / 2)
		while (--zeroIdx >= 0)
		{
			check_AB_Swap(s, s->interval);
			ra(s);
		}
	else
		while (++zeroIdx <= s->sizeA)
		{
			check_AB_Swap(s, s->interval);
			rra(s);
		}
	check_AB_Swap(s, s->interval);
}