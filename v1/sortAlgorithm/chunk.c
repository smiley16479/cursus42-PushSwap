#include "../utils.h"

int chunkCmp(int toCmp, int chunkSize, int *chunk)
{
	while (chunkSize--)
		if (chunk[chunkSize] == toCmp)
			return 1;
	return 0;
}

int *nearestPopableAB(stacks *s, int chunkSize, int chunkIdx)
{
	int i;
	int j;

	i = 0;
	j = chunkSize - 1;
	while (i < j)
	{
		if (chunkCmp(s->tackA[i], chunkSize, s->tackSort + chunkIdx))
			return i;
		if (chunkCmp(s->tackA[j], chunkSize, s->tackSort + chunkIdx))
			return j;
		++i;
		--j;
	}
	return -1;
}

void midPointAlgo(stacks *s)
{
	int chunkSize;
	int i;

	i = -1;
	chunkSize = s->size / 2;
	while (++i < chunkSize)
	{
		
	}
}