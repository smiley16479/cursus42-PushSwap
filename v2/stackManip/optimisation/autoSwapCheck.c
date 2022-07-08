#include "utils.h"

/* 
** Check si un swap est possible sur la/les stack/s
** pour un swap strict, spécifier un interval de 1.
*/
inline int check_A_Swap(stacks *s, int interval)
{
	if (s->sizeA >= 2 && s->l_A->idx > s->l_A->next->idx
		&& s->l_A->idx - s->l_A->next->idx <= interval)
	{
		fprintf(stderr, "Check_A idx : %d, idx->next : %d interval : %d\n", s->l_A->idx, s->l_A->next->idx, interval);
		return (1);
	}
	return (0);
}

inline int check_B_Swap(stacks *s, int interval)
{
	if (s->sizeB >= 2 && s->l_B->idx < s->l_B->next->idx
		&& s->l_B->next->idx - s->l_B->idx <= interval)
		return (1);
	return (0);
}

int check_AB_Swap(stacks *s, int interval)
{
	int a;
	int b;

	if (s->sizeA >= 2 && s->l_A->stay)
		a = check_A_Swap(s, interval);
	else 
		a = e_false;
	if (s->sizeB >= 2 && s->l_B->stay)
		b = check_B_Swap(s, interval);
	else 
		b = e_false;
	if (a || b)
	{
		if (a && b)
			ss(s);
		else if (a)
			sa(s);
		else if (b)
			sb(s);
		return (1);
	}
	return (0);
}
