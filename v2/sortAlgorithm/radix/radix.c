#include "utils.h"

void radixAlgo(stacks *s)
{
	int i;
	int chunkIdx;
	int chunkSize;

	chunkIdx = 0;
	chunkSize = s->size;
	while ((chunkSize /= 2) && (i = -1))
	{
		while (++i < chunkSize)
			popAB(s, nearestPopableAB_radix(s, chunkSize, chunkIdx), 1);
		chunkIdx += chunkSize;
	}
}

void printBin(int nb, int octet)
{
	int i;

	i = octet * 8;
	while (i)
		printf("%d", (0x1 & (nb >> --i)));
	printf("\n");
}

int nearestPopableAB_radix(stacks *s, int chunkSize, int chunkIdx)
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


// int main()
// {
// 	printf("%s\n",( -2 & 1) ? "yes": "no");
// 	printBin(-3, sizeof(int));
// 	printBin(-4, sizeof(int));
// 	printBin(2147483649, sizeof(int));
// 	printBin(2147483650, sizeof(int));
// 	printBin(2147483651, sizeof(int));
// 	printBin(2147483652, sizeof(int));
// 	printf("%d\n", 2147483652);
// 	return 0;
// }