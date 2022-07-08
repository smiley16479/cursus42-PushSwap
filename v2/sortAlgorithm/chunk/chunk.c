#include "utils.h"
int sort_BA_uniq(stacks *s); // A virer, c pour tester

/*
**	is toCmp == à l'un des éléments de l'interval chunksize contenu ds *chunkSort
*/
int chunkCmp(int toCmp, int chunkSize, int *chunkSort, int ascending)
{
	// fprintf(stderr ,"chunkSize %d, ascending %d\n", chunkSize, ascending);
	if (ascending)
	{
		while (chunkSize--)
			if (*chunkSort++ == toCmp)
				return 1;
	}
	else
	{
		while (chunkSize--)
			if (*--chunkSort == toCmp)
				return 1;
	}
	return 0;
}

int nearestPopableAB(stacks *s, int chunkSize, int chunkIdx)
{
	int i;
	int j;
	t_node *node[2];

	i = 0;
	j = s->sizeA - 1;
	node[0] = s->l_A;
	node[1] = s->l_A->prev;
	// printf("nearestPopableAB chunkSize : %d, s->sizeA : %d, chunkIdx %d\n",chunkSize, s->sizeA, chunkIdx);
	while (i <= s->sizeA / 2)
	{
		if (chunkCmp(node[0]->data, chunkSize, s->tackSort + chunkIdx, 1))
			return i;
		if (chunkCmp(node[1]->data, chunkSize, s->tackSort + chunkIdx, 1))
			return j;
		node[0] = node[0]->next;
		node[1] = node[1]->prev;
		++i;
		--j;
	}
	return -1;
}

/* 
** Pareil que nearestPopableAB mais prennant compte des r. ou rr. réalisés
*/
int sortAB(stacks *s, int chunkSize, int chunkIdx)
{

}

int sortBA(stacks *s, int chunkSize, int *chunkIdx)
{
	printf("sortBA : chunkSize %d, chunkIdx %d\n", chunkSize, *chunkIdx);
	int i;
	int j;
	static int pas;
	static int rbs;
	t_node *node[2];

	i = 0;
	pas = 0;
	rbs = 0;
	j = s->sizeB - 1;
	node[0] = s->l_B;
	node[1] = s->l_B->prev;
	while (i <= s->sizeB / 2)
	{
		if (chunkCmp(node[0]->data, chunkSize, s->tackSort + *chunkIdx, 0))
		{
			rbs += i;
			*chunkIdx -= chunkSize;
			return i;
		}
		if (rbs)
		{
			if (chunkCmp(node[1]->data, chunkSize, s->tackSort + *chunkIdx, 0))
			{
				rbs -= j;
				*chunkIdx -= chunkSize;
				return j;
			}
			node[1] = node[1]->prev;
			--j;
		}
		node[0] = node[0]->next;
		++i;
	}
	*chunkIdx -= chunkSize;
	return -1;
}

/* 
** Pop le bon élément de A vers B en checkant si des swap sont néccessaire à chaque manip de A
*/
void popAB(stacks *s, int idx, int swapInterval)
{
	if (idx == -1) {
		printf("popAB() idx == -1 (popAB non trouvé)\n");
		exit(1);
	}
	if (idx <= s->sizeA / 2)
		while (--idx >= 0)
		{
			// if (check_AB_Swap(s, swapInterval))
			// 	sa(s);
			ra(s);
		}
	else
		while (++idx <= s->sizeA)
		{
			// if (check_AB_Swap(s, swapInterval))
			// 	sa(s);
			rra(s);
		}
	pb(s);
	// check_AB_Swap(s, swapInterval);
}

void midPointAlgo(stacks *s)
{
	int i;
	int chunkIdx;
	int chunkSize;
	
	chunkIdx = 0;
	chunkSize = s->size;
	while ((chunkSize /= 2) && (i = -1))
	{
		// printf("chunk size %d, chunkIdx : %d\n", chunkSize, chunkIdx);
		// printf("list A\n");
		// printList(s->l_A, s->sizeA);
		// printf("list B\n");
		// printList(s->l_B, s->sizeB);
		while (++i < chunkSize)
			popAB(s, nearestPopableAB(s, chunkSize, chunkIdx), 1);
		chunkIdx += chunkSize;
	}
	// printf("Size A : %d, chunkSize %d\n", s->sizeA, chunkSize);
	
	sort_BA_uniq(s);
	
	// Seconde partie "back and forth"
/* 	while (chunkSize < s->size / 2 && (i = -1))
	{
		while (++i < chunkSize)
			sortBA(s, chunkSize, &chunkIdx);
		// while (!isSorted(s->l_A, chunkSize, 1))
		// {

		// }
		// while (!isSorted(s->l_B, chunkSize, 0))
		// {

		// }
		chunkSize *= 2;
	} */
		// printf("chunk size %d, chunkIdx : %d\n", chunkSize, chunkIdx);
		fprintf(stderr, "list A\n");
		printList(s->l_A, s->sizeA);
		fprintf(stderr, "list B\n");
		printList(s->l_B, s->sizeB);
}