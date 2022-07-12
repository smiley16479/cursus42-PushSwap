#include "utils.h"

/*
** **arr contient le nombre d'élem qui se suivent : par index de l_A[i] modifié par
** l_cpy[0]->data > l_cpy[0]->next->data (le premier *ptr), puis l'idx à partir duquel
** partir ds l_A[i] (le second *ptr) pour avoir le max d'elem qui se suivent
** getMaxFollowedElem retourne les index à partir desquel partir pour avoir le max 
** d'elem qui se suivent ds la première partie du long le premier index ds la seconde le second
*/
long	getMaxFollowedElem(int **arr, int size)
{
	int idx[2] = {0};

	int i, j;
	i = j = -1;
	while(arr[++i] && (j = -1))
		while(++j < size)
			if (arr[idx[0]][idx[1]] < arr[i][j])
			{
				idx[0] = i;
				idx[1] = j;
			}
	// fprintf(stderr, "idx[0] av le plus d'elem qui se suivent : arr[%d][%d] : %d\n", idx[0], idx[1], arr[idx[0]][idx[1]]);
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
	// fprintf(stderr, "(getLowestIdx) index av le plus d'elem qui se suivent : arr[%d] : %d\n", index, arr[index]);
	// for (size_t i = 0; i < size; i++)
	// 	fprintf(stderr, "arr[%d]: %d\n", i, arr[i]);
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
		// fprintf(stderr, "followedElem() starting from %d\n", l->data);
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
				// fprintf(stderr, " ? %d < %d\n", elem , l->data);
				l->stay = e_true;
			}
			elem = l->data;
		}
	}
	// if (markElem)
		// fprintf(stderr, "followedElem : %d starting from %d\n", count_Of_Followed_Elem, l->data);
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
	// fprintf(stderr, "new followed item account : %d\n", tab[lowestIndex]); // no need
	// l = &(s->l_A[lowestIndex]); // no need
	// followedElem(l, s->size, e_true); // no need
	// printList(l, s->size); // no need
	free(tab);
	return (lowestIndex);
}



void gtSort_swapFurther(stacks *s)
{
	int i;
	long idx;

	if (s->sizeA <= 4 && sort_4orLessNb(s))
			return;
	int interval = s->sizeA / 5 ? s->sizeA / 5 : 1;
	int **tab = malloc(sizeof(int**) * (interval + 1));
	ft_bzero(tab, sizeof(int**) * (interval + 1));
	// fprintf(stderr, "elem_to_keep_gtSort_swapFurther\n");
	while (interval > 0)
	{
		tab[((s->sizeA / 5) ? s->sizeA / 5 : 1) - interval] = elem_to_keep_gtSort_swapFurther(s, interval);
		--interval;
	}
	idx = getMaxFollowedElem(tab, s->sizeA);
	s->interval = s->sizeA / 5 - ((idx << 32) >> 32);
	// fprintf(stderr, "les indexes %d: %d\n", ((idx << 32) >> 32), (idx >> 32));
	markElem2keep_gtSort_swapFurther(s, (idx >> 32), s->sizeA / 5 - ((idx << 32) >> 32));
	AB_nothinButTrue(s, tab[((idx << 32) >> 32)][(idx >> 32)], s->sizeA / 5 - ((idx << 32) >> 32));
	// printList(s->l_A, s->sizeA);
	while (s->sizeB)
		nearestInserableBA_gt(s);
	align(s);
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void gtSort_Family_Algorithm(stacks *s)
{
	int lowestIndex[2];
	gtSort_swapFurther(s);
	
	// if (!isSorted(s->l_A, s->sizeA, e_true))
	// {
	// 	fprintf(stderr, "NOT SORTED :'(\n");
	// 	exit(404);
	// }

	// fprintf(stderr, "\nelem_to_keep_gtSort_swap\n");
	// lowestIndex[1] = elem_to_keep_gtSort_swap(s);
	// fprintf(stderr, "\nelem_to_keep_gtSort_swap result %d\n", lowestIndex[1]);

	// fprintf(stderr, "\nelem_to_keep_gtSort\n");
	// *lowestIndex = elem_to_keep_gtSort(s);
}

// 8 19 10 14 11 16 7 2 18 0 9 13 1 5 15 12 17 6 4 3