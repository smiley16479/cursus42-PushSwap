#include "utils.h"

/* 
** Retourne l'index de l'elem ds s->tackSort
*/

int get_index(stacks *s, int elem)
{
	int i;

	i = s->size;
	while (i--)
		if (s->tackSort[i] == elem)
			return i;
	return -1;
}