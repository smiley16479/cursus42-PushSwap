#include "../utils.h"

/* 
**	is toCmp == à l'un des éléments de l'interval chunksize contenu ds *chunk
*/
int chunkCmp(int toCmp, int chunkSize, int *chunkSort, int ascending)
{
	printf("chunkSize %d, ascending %d\n", chunkSize, ascending);
	while (chunkSize--)
		if (ascending)
		{
			if (*chunkSort++ == toCmp)
				return 1;
		}
		else
		{
			if (*chunkSort-- == toCmp)
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
	printf("nearestPopableAB chunkSize : %d, s->sizeA / 2 : %d, chunkIdx %d\n",chunkSize, s->sizeA / 2, chunkIdx);
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

int sortBA(stacks *s, int chunkSize, int chunkIdx)
{
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
		if (chunkCmp(node[0]->data, chunkSize, s->tackSort + chunkIdx, 0))
		{
			rbs += i;
			return i;
		}
		if (rbs)
		{
			if (chunkCmp(node[1]->data, chunkSize, s->tackSort + chunkIdx, 0))
			{
				rbs -= j;
				return j;
			}
			node[1] = node[1]->prev;
			--j;
		}
		node[0] = node[0]->next;
		++i;
	}
	return -1;
}

/* 
** Pop le bon élément de A vers B en checkant si des swap sont néccessaire à chaque manip de A
*/
void popAB(stacks *s, int idx)
{
	if (idx == -1) {
		printf("popAB() idx == -1 (nearestPopableAB non trouvé)\n");
		exit(1);
	}
	if (idx < s->sizeA / 2)
		while (--idx >= 0)
		{
			if (check_A_Swap(s))
			{
				sa(s);
				if (idx < 0)
					break ;
			}
			ra(s);
		}
	else
		while (++idx <= s->sizeA)
		{
			if (check_A_Swap(s))
				sa(s);
			rra(s);
		}
	pb(s);
	check_AB_Swap(s);
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
		printf("chunk size %d, chunkIdx : %d\n", chunkSize, chunkIdx);
		printf("list A\n");
		printList(s->l_A, s->sizeA);
		printf("list B\n");
		printList(s->l_B, s->sizeB);
		while (++i < chunkSize)
			popAB(s, nearestPopableAB(s, chunkSize, chunkIdx));
		chunkIdx += chunkSize;
	}
	// Seconde partie de "back and forward"
	// ++chunkSize;
	// while (s->sizeA != s->size)
	// {
	// 	while (!isSorted(s->l_A, chunkSize, 1))
	// 	{

	// 	}
	// 	while (!isSorted(s->l_B, chunkSize, 0))
	// 	{

	// 	}
	// 	chunkSize *= 2;
	// }


		printf("chunk size %d, chunkIdx : %d\n", chunkSize, chunkIdx);
		printf("list A\n");
		printList(s->l_A, s->sizeA);
		printf("list B\n");
		printList(s->l_B, s->sizeB);
}