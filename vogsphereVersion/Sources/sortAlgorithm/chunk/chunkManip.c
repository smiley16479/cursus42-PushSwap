#include "utils.h"
int chunkCmp(int toCmp, int chunkSize, int *chunkSort, int ascending);

int nearestPopableBA(stacks *s)
{
	int i;
	int j;
	t_node *node[2];
	fprintf(stderr, "s->tackSort + s->sizeB : %d\n", *s->tackSort + s->sizeB);
	i = 0;
	j = s->sizeB - 1;
	node[0] = s->l_B;
	node[1] = s->l_B->prev;
	while (i <= s->sizeB / 2)
	{
		if (chunkCmp(node[0]->data, 1, s->tackSort + s->sizeB , 0))
		{
			fprintf(stderr, "node[0]->data : %d\n", node[0]->data);
			return i;
		}
		if (chunkCmp(node[1]->data, 1, s->tackSort + s->sizeB , 0))
		{
			fprintf(stderr, "node[1]->data : %d\n", node[1]->data);
			return j;
		}
		node[0] = node[0]->next;
		node[1] = node[1]->prev;
		++i;
		--j;
	}
	return -1;
}

/* 
** Pop le bon élément de B vers A en checkant si des swap sont néccessaire à chaque manip de B
*/
void popBA(stacks *s, int idx)
{
	if (idx == -1) {
		fprintf(stderr,"popBA() idx == -1 (nearestPopableAB non trouvé)\n");
		t_node *node = s->l_A;
		for (size_t i = 0; i < s->sizeA; i++) 
		{
			fprintf(stderr, "%d\n", node->data);
			node = node->next;
		}
		
		// printf("acrion %d\n", s->idxAction * 2);
		readAction(s);
		exit(1);
	}
	if (idx < s->sizeB / 2)
		while (--idx >= 0)
		{
			if (check_B_Swap(s, 1))
			// { // est-ce que c utile ça ?
				sb(s);
			// 	if (idx < 0)
			// 		break ;
			// }
			rb(s);
		}
	else
		while (++idx <= s->sizeB)
		{
			if (check_B_Swap(s, 1))
				sb(s);
			rrb(s);
		}
	pa(s);
	check_AB_Swap(s, 1);
}

int sort_BA_uniq(stacks *s)
{
	while (s->sizeB)
		popBA(s, nearestPopableBA(s));
}
