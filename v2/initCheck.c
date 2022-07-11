#include "utils.h"

void panicERROR(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int checkDuplicate(stacks *s)
{
	int i;
	int j;
	int tmp;

	i = 0;
	while (i < s->size)
	{
		tmp = s->l_A[i].data;
		j = ++i;
		while (j < s->size)
			if (tmp == s->l_A[j++].data)
				return (1);
	}
	return (0);
}

int checkArg(char *av[], stacks *s)
{
	int i;

	while (*av)
	{
		i = 0;
		if ((*av)[i] == '-' || (*av)[i] == '+')
			if (!(*av)[++i])
				return (1);
		while ((*av)[i])
		{
			if ('0' > (*av)[i] || (*av)[i] > '9')
				return (1);
			++i;
		} 
		s->tackSort[s->size] = putNb(*av);
		s->l_A[s->size].data = s->tackSort[s->size];
		++s->size;
		++av;
	}
	// for (size_t i = 0; i < s->size; i++)
	// 	fprintf(stderr, "%d\n", s->tackSort[i]);
	s->sizeA = s->size;
	s->sizeB = 0;
	return (checkDuplicate(s));
}

int putNb(char *strNb)
{
	long nb;
	int sign;

	if (!strNb || !(*strNb))
		panicERROR();
	sign = 1;
	if(*strNb == '-' && ++strNb)
		sign = -1;
	nb = 0;
	while (*strNb)
	{
		nb *= 10;
		nb += *strNb++ - '0';
	}
	if (nb > __INT_MAX__ || nb < -2147483648)
		panicERROR();
	return (nb * sign);
}

void sort(int *array, int size)
{
	int i;
	int j;
	int *tmp;
	int swap;

	i = -1;
	while (++i < size)
	{
		j = i;
		tmp = &array[i];
		while (++j < size)
			if (array[j] < *tmp)
				tmp = &array[j];
		if (tmp !=  &array[i])
		{
			swap = *tmp;
			*tmp = array[i];
			array[i] = swap;
		}
	}
}
