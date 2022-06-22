#include "utils.h"

/* 
** A la diff de "check_A_Swap" celui-ci check avec comme point de départ *l
** l'autre test uniquement le haut de la stack
*/
int check_A_Swap_for_gt(stacks *s, t_node *l, t_bool markElem)
{
	int i;

	if (s->sizeA < 2)
		return (0);
	i = 0;
	while (i < s->size && s->tackSort[i] != l->data)
		++i;
	if (i)
		if (l->next->data == s->tackSort[i - 1])
		{
			if (markElem)
			{
				l->stay = e_swap1;
				l->next->stay = e_swap2;
			}
			return (1);
		}
	return (0);
}

/*
** Check cb d'élem se suivent en fonction de l'index de *l
*/
int *testWithNewConfig(stacks *s, t_node *l)
{
	int *tab, lowestIndex, i;
	tab = malloc(s->size * sizeof(int));
	if (!tab)
		exit(-1);
	fprintf(stderr, "testWithNewConfig1 (from %d) %p\n", l->data, l);
	i = -1;
	while (++i < s->size)
	{
		tab[i] = followedElem(l, s->size, e_false);
		l = l->next;
	}
	lowestIndex = getLowestIdx(tab, s->size); // ici c'est l'index où il y a le plus de nb qui se suivent
	for (size_t i = 0; i < lowestIndex; i++)
		l= l->next;
	// lowestIndex = followedElem(l, s->size, e_true); // ici le nb de nb qui se suivent no need just to see elem selectect in the best config
	
	// printList(l, s->size);
	fprintf(stderr, "(testWithNewConfig2) new followed item account : %d (from %d)\n", tab[lowestIndex], l->data);

	// free(tab);
	return tab;
}

/* 
** Check si le swap_strict d'éléments augmente les éléments conservés ds A
*/
int elem_to_keep_gtSort_swap(stacks *s)
{
	t_node *l_cpy[2];
	int i;
	int j;
	int **tab;
	if (!(tab = malloc(s->size * sizeof(int*))))
		exit(-1);
	i = -1;
	while (++i < s->sizeA)
	{
		l_cpy[0] = ft_lstCpy(s->l_A, s->size);
		l_cpy[1] = l_cpy[0];
		l_cpy[0] += i;
		fprintf(stderr, "l_cpy.data (gtSort_swap): i : %d  data : %d ptr : %p - %p\n", i , l_cpy[0]->data, l_cpy[0], l_cpy[1]);
		// printList(l_cpy[1], s->size);
		j = 0;
		while (j++ < s->sizeA)
		{
			// if (check_A_Swap_for_gt(s, l_cpy[0], e_false))
			if (l_cpy[0]->data > l_cpy[0]->next->data) // && l_cpy[0]->next->data != s->l_A->prev->data)
			{
				// (*l_cpy)->next->stay = e_true;
				// (*l_cpy) = (*l_cpy)->next;
				// ++i;
				swap(*l_cpy);
			}
			l_cpy[0] = l_cpy[0]->next;
		}
		tab[i] = testWithNewConfig(s, l_cpy[0]);
		// count_n_clear_True(l_cpy[0], s->sizeA);
		printList(l_cpy[0], s->size);
		fprintf(stderr, "\n-------------------\n");
		// printList(l_cpy[1], s->size);
		// fprintf(stderr, "\n-------------------\n");
		free(l_cpy[1]);
	}
	fprintf(stderr, "hihest following elem %d\n", l_cpy[0]->data, l_cpy[1]->data, l_cpy[0], l_cpy[1]);


	fprintf(stderr, "Pour CHECK\n");
	long idx = getMaxFollowedElem(tab, s->size);
	l_cpy[0] = ft_lstCpy(s->l_A, s->size);
	l_cpy[0] += ((idx << 32) >> 32);
	fprintf(stderr, "Pour CHECK begin with elem %d\n", l_cpy[0]->data);
	j = 0;
	while (j++ < s->sizeA)
	{
		// if (check_A_Swap_for_gt(s, l_cpy[0], e_false))
		if (l_cpy[0]->data > l_cpy[0]->next->data) // && l_cpy[0]->next->data != s->l_A->prev->data)
		{
			// (*l_cpy)->next->stay = e_true;
			// (*l_cpy) = (*l_cpy)->next;
			// ++i;
			swap(*l_cpy);
		}
		l_cpy[0] = l_cpy[0]->next;
	}
	fprintf(stderr, "OUI OUI oUI %d\n", followedElem(l_cpy[0] + (idx >> 32), s->size, e_true) /* testWithNewConfig(s, l_cpy[0]) */);
	printList(l_cpy[0], s->size);

	return (0);
}
/*
** on retourne donc l + getLowestIdx() -> qui est l'élem à partir duquel faire l'algo
** (l_cpy[0]->data > l_cpy[0]->next->data) déclenchera le plus de d'élem qui se suivent
**
*/

// 8 19 10 14 11 16 7 2 18 0 9 13 1 5 15 12 17 6 4 3