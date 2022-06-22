#include "utils.h"

/*
** **arr contient le nombre d'élem qui se suivent par index de l_A[i] modifié par
** l_cpy[0]->data > l_cpy[0]->next->data (le premier *ptr), puis l'idx à partir duquel
** on prends l_A[i] (le second *ptr) dans lequel sont le nombre d'elem qui se suivent
** getMaxFollowedElem retourne l'index à partir duquel partir pour avoir le max d'elem qui se suivent
*/
long	getMaxFollowedElem(int **arr, int size)
{
	int idx[2] = {0};

	int i, j;
	i = j = -1;
	while(++i < size && (j = -1))
		while(++j < size)
			if (arr[idx[0]][idx[1]] < arr[i][j])
			{
				idx[0] = i;
				idx[1] = j;
			}
	fprintf(stderr, "idx[0] av le plus d'elem qui se suivent : arr[%d][%d] : %d\n", idx[0], idx[1], arr[idx[0]][idx[1]]);
	return *((long*)idx);
}


/*
** *arr contient le nombre d'élem qui se suivent par index de l_A[i], getLowestIdx
** retourne l'index min où le nombre d'élem qui se suivent est le plus grand
*/
int	getLowestIdx(int *arr, int size)
{
	int index;
	int i;

	i = -1;
	index = 0;
	while(++i < size)
		if (arr[index] < arr[i])
			index = i;
	fprintf(stderr, "index av le plus d'elem qui se suivent : arr[%d] : %d\n", index, arr[index]);
	for (size_t i = 0; i < size; i++)
		fprintf(stderr, "arr[%d]: %d\n", i, arr[i]);
	return index;
}

/* 
** Count number of elements greater than each other through the stack (a < b < c etc.)
*/
int followedElem(t_node *l, int size, t_bool markElem)
{
	int count_Of_Followed_Elem;
	int elem;

	if (markElem)
	{
		fprintf(stderr, "followedElem() starting from %d\n", l->data);
		l->stay = e_true;
	}
	elem = l->data;
	count_Of_Followed_Elem = 1;
	while (size--)
	{
		l = l->next;
		if (elem < l->data && ++count_Of_Followed_Elem)
		{
			if (markElem)
			{
				fprintf(stderr, " ? %d < %d\n", elem , l->data);
				l->stay = e_true;
			}
			elem = l->data;
		}
	}
	if (markElem)
		fprintf(stderr, "followedElem : %d starting from %d\n", count_Of_Followed_Elem, l->data);
	return count_Of_Followed_Elem;
}

int elem_to_keep_gtSort(stacks *s)
{
	t_node *l;
	int lowestIndex;
	int *tab;
	int i;

	tab = malloc(s->size * sizeof(int));
	if (!tab)
		exit(-1);
	i = -1;
	l = s->l_A;
	while (++i < s->size)
	{
		tab[i] = followedElem(l, s->size, e_false);
		l = l->next;
	}
	lowestIndex = getLowestIdx(tab, s->size);
	fprintf(stderr, "new followed item account : %d\n", tab[lowestIndex]); // no need
	l = &(s->l_A[lowestIndex]); // no need
	followedElem(l, s->size, e_true); // no need
	printList(l, s->size); // no need
	free(tab);
	return (lowestIndex);
}

void isBetterAfterSwap(stacks *s)
{
	int lowestIndex[2];
	int i = 0;

	// int interval = s->sizeA / 10;
	// int **tab = malloc(sizeof(int**)* interval);
	// fprintf(stderr, "elem_to_keep_gtSort_swapFurther\n");
	// while (interval)
	// 	tab[i++] = elem_to_keep_gtSort_swapFurther(s, interval--, e_false);

	fprintf(stderr, "\nelem_to_keep_gtSort_swap\n");
	lowestIndex[1] = elem_to_keep_gtSort_swap(s);
	// fprintf(stderr, "\nelem_to_keep_gtSort_swap result %d\n", lowestIndex[1]);

	// fprintf(stderr, "\nelem_to_keep_gtSort\n");
	// *lowestIndex = elem_to_keep_gtSort(s);
}

/* 
** copie de select_suitSort_pb(stacks *s) adapté pour marqué les elem à 
** conserver ds gt_sort ceci est censé amélioré elem_to_keep_gtSort_swap(s)
** Il ne fait que marquer les elem à conserver et ne change rien 
*/
int *elem_to_keep_gtSort_swapFurther(stacks *s, int interval, t_bool markElem)
{
	int *tab = malloc(sizeof(int)* s->sizeA);
	int i[4];
	int j = -1;
	int elem;
	t_node *l;

	while (++j < s->sizeA)
	{
		l = s->l_A + j;
		elem = l->data;
		i[0] = 0;
		while (i[0] < s->sizeA)
		{
			i[1] = get_index(s, l->data);
			i[2] = get_index(s, l->next->data);
			i[3] = get_index(s, l->next->next->data);
			fprintf(stderr, "%3d, %3d, %3d, %8d\n", l->data, l->next->data, l->next->next->data, i[0]);
			// fprintf(stderr, "%3d, %3d, %3d\n", i[1], i[2], i[3]);
			// Ds l'ordre
			if (elem <= l->data && i[2] - i[1] > 0 && i[2] - i[1] <= interval)
			{
				l->stay = e_true;
				l->next->stay = e_true;
				elem = l->next->data;
				fprintf(stderr, "True (i : %d)\n\n", i[0]);
			}
			// Ds l'ordre avec un gap entre [1] et [3]
			else if (elem <= l->data && i[3] - i[1] > 0 && i[3] - i[1] <= interval)
			{
				l->stay = e_true;
				l->next->stay = e_false;
				l->next->next->stay = e_true;
				elem = l->next->next->data; // [3].data
				l = l->next;
				++i[0];
				fprintf(stderr, "True False True (i : %d)\n\n", i[0]);
			}
			// Ds le désordre
			else if (elem <= l->data && i[1] - i[2] > 0 && i[1] - i[2] <= interval)
			{
				l->stay = e_swap1;
				l->next->stay = e_swap2;
				elem = l->data;
				fprintf(stderr, "True (i : %d)\n\n", i[0]);
			}
			// Ds le désordre avec un gap entre [1] et [3]
			else if (elem <= l->data && i[1] - i[3] > 0 && i[1] - i[3] <= interval)
			{
				l->stay = e_swapGap1;
				l->next->stay = e_false;
				l->next->next->stay = e_swapGap2;
				elem = l->data; // [1].data
				l = l->next;
				++i[0];
				fprintf(stderr, "True False True (i : %d)\n\n", i[0]);
			}
			else if (i[0] < s->sizeA - 1)
			{
				if (!l->stay) // ? wtf
					l->stay = e_false;
				// l->next->stay = e_false;
				// l = l->next;
				// ++i[0];
				fprintf(stderr, "False (i : %d)\n\n", i[0]);
			}
			l = l->next;
			++i[0];
		}
		tab[j] = count_n_clear_True(l, s->sizeA);
	}
	return (tab);
}

