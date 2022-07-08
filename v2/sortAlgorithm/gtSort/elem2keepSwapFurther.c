#include "utils.h"


/* 
** copie de select_suitSort_pb(stacks *s) adapté pour marqué les elem à 
** conserver ds gt_sort ceci est censé amélioré elem_to_keep_gtSort_swap(s)
** Il ne fait que marquer les elem à conserver et ne change rien 
** interval est l'écart en dessous duquel deux valeurs seront gardées
*/
int *elem_to_keep_gtSort_swapFurther(stacks *s, int interval)
{
	int *tab = malloc(sizeof(int)* s->sizeA);
	t_node *l[4]; // [0] elem to compare // [1] current node // [2] current->next node // [3] current->next->next node
	int i[2];
	
	i[0] = -1;
	while (++i[0] < s->sizeA)
	{
		l[1] = s->l_A + i[0];
		l[1]->stay = e_true;
		l[0] = l[1];
		i[1] = 0;
		// fprintf(stderr, "\ns->l_A (%d) + i[0] : %d\n\n", l[1]->data, i[0]);
		while (i[1] < s->sizeA)
		{
			l[2] = l[1]->next;
			l[3] = l[2]->next;
			if (l[1]->idx - l[0]->idx > 0 && l[1]->idx - l[0]->idx <= interval)
			{
				l[1]->stay = e_true;
				l[0] = l[1];
				// fprintf(stderr, "(1) (i : %d) elem : %d\n", i[1], l[0]->data);
			} // désordre
			else if (l[0]->idx - l[1]->idx > 0 && l[0]->idx - l[1]->idx <= 1/* interval */) // <--ICI
			{
				l[0]->stay = e_swap1;
				l[1]->stay = e_swap2;
				// fprintf(stderr, "(1'') (i : %d) elem : %d\n", i[1], l[0]->data);
			}
			l[1] = l[2];
			++i[1];
		}
		// if (interval == 4 && !i[0]){
			fprintf(stderr, "\nICICICICICIC 1st maillon : %d interval : %d\n", l[1]->data, interval);
			printList(l[1], s->size);
		// }
		tab[i[0]] = count_n_clear_True(l[1], s->sizeA);
		fprintf(stderr, "\nElement true : %d interval : %d\n", tab[i[0]], interval);
	}
	// for (size_t i = 0; i < s->sizeA; i++)
	// 	fprintf(stderr, "elem to keep  tab[%d] : %d\n", i, tab[i]);
	return (tab);
}

void markElem2keep_gtSort_swapFurther(stacks *s, int idx, int interval)
{
	t_node *l[4]; // [0] elem to compare // [1] current node // [2] current->next node // [3] current->next->next node
	int i;

	i = -1;
	count_n_clear_True(s->l_A + idx, s->sizeA);
	l[0] = s->l_A + idx;
	l[1] = s->l_A + idx;
	l[1]->stay = e_true;
	fprintf(stderr, "markElem2keep_gtSort_swapFurther\n");
	fprintf(stderr, "(1) (i : %d) elem : %d\n", i, l[0]->data);
	while (++i < s->sizeA)
	{
		l[2] = l[1]->next;
		l[3] = l[2]->next;
		if (l[1]->idx - l[0]->idx > 0 && l[1]->idx - l[0]->idx <= interval)
		{
			l[1]->stay = e_true;
			l[0] = l[1];
			fprintf(stderr, "(2) (i : %d) elem : %d\n", i, l[0]->data);
		} // désordre
		else if (l[0]->idx - l[1]->idx > 0 && l[0]->idx - l[1]->idx <= 1/* interval */) // <--ICI
		{
			l[0]->stay = e_swap1;
			l[1]->stay = e_swap2;
			fprintf(stderr, "(3) (i : %d) elem : %d\n", i, l[1]->data);
		}
		l[1] = l[2];
	}
	// fprintf(stderr, "\nmarkElem2keep_gtSort_swapFurther(t_node *l_node, int size, int interval)\n");
	// printList(l[1], size);
}

// garde slmt les element != de e_false ds A
// Checkant si des swap sont nécessaire selon: int swapInterval
void AB_nothinButTrue(stacks *s, int trueElem, int swapInterval)
{
	fprintf(stderr, "\nAB_nothinButTrue\n");

	t_node *l;
	int i;
	int idx;

	i = 0;
	s->maxIdx = 0;
	s->minIdx = s->size;
	while(i < s->size)
	{
		if ((idx = nearestPopableTrueAB_gt(s)) != -1)
			popAB(s, idx, swapInterval);
		++i;
	}
	// initialisation minIdx maxIdx
	i = -1;
	l = s->l_A;
	while(++i < s->sizeA)
	{
		if (s->minIdx > l->idx)
			s->minIdx = l->idx;
		if (s->maxIdx < l->idx)
			s->maxIdx = l->idx;
		l = l->next;
	}
}

/*
** nearestPopableTrueAB_gt pour SwapFurther où le swap est fait en fonction du stay == false
*/
int nearestPopableTrueAB_gt(stacks *s)
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
		if (node[0]->stay == e_false)
			return i;
		if (node[1]->stay == e_false)
			return j;
		node[0] = node[0]->next;
		node[1] = node[1]->prev;
		++i;
		--j;
	}

	fprintf(stderr, "nearestPopableTrueAB_gt e_false Non Trouvé\n");
	printList(s->l_A, s->sizeA);	
	return -1;
}
