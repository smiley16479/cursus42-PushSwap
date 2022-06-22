#include "utils.h"

// void radixAlgo(stacks *s)
// {
// 	int i;
// 	int chunkIdx;
// 	int chunkSize;
	
// 	chunkIdx = 0;
// 	chunkSize = s->size;
// 	while ((chunkSize /= 2) && (i = -1))
// 	{
// 		while (++i < chunkSize)
// 			popAB(s, nearestPopableAB(s, chunkSize, chunkIdx));
// 		chunkIdx += chunkSize;
// 	}
// }

void printBin(int nb, int octet)
{
	int i;

	i = octet * 8;
	while (i)
		printf("%d", (0x1 & (nb >> --i)));
	printf("\n");
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