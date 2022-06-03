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
		tmp = s->tack[i];
		j = ++i;
		while (j < s->size)
			if (tmp == s->tack[j++])
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
		s->tack[s->size] = putNb(*av);
		s->tackSort[s->size] = s->tack[s->size];
		s->l_A[s->size].data = s->tack[s->size];
		++s->size;
		++av;
	}
	s->sizeA = s->size;
	s->sizeB = 0;
	return (checkDuplicate(s));
}

int putNb(char *strNb)
{
	int nb;
	int sign;

	nb = 0;
	if(*strNb == '-' && ++strNb)
		sign = -1;
	else 
		sign = 1;
	while (*strNb)
	{
		nb *= 10;
		nb += *strNb++ - '0';
	}
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

void ft_bzero(void *s, int n)
{
	int i;

	i = -1;
	while (++i < n)
		*(char *)s++ = 0;
}
