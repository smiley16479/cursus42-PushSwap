#include "utils.h"

/* 
** Check si un swap est possible sur la/les stack/s
*/
int check_A_Swap(stacks *s)
{
	int i;

	if (s->sizeA < 2)
		return (0);
	i = 0;
	while (i < s->size && s->tackSort[i] != s->l_A->data)
		++i;
	if (i)
		if (s->l_A->next->data == s->tackSort[i - 1])
			return (1);
	return (0);
}

int check_B_Swap(stacks *s)
{
	int i;

	if (s->sizeB < 2)
		return (0);
	i = 0;
	while (i < s->size && s->tackSort[i] != s->l_B->data)
		++i;
	if (i < s->size - 1)
		if (s->l_B->next->data == s->tackSort[i + 1])
			return (1);
	return (0);
}

int check_AB_Swap(stacks *s)
{
	int a;
	int b;

	a = check_A_Swap(s);
	b = check_B_Swap(s);
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
