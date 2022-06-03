#include "utils.h"

int main(int ac, char *av[])
{
	stacks s;
	init(ac, av,&s);

	for (size_t i = 0; i < s.sizeA; i++)
		printf("%d\n", s.tackA[i]);

	free(s.tackA);
	free(s.tackB);
	return (0);
}

void init(int ac, char *av[], stacks *s)
{
	s->size = ac;
	s->tack = malloc(sizeof(*s->tackA) * s->size);
	s->tackA = malloc(sizeof(*s->tackA) * s->size);
	s->tackB = malloc(sizeof(*s->tackB) * s->size);
	s->sizeA = s->sizeB = 0;
	if (!s->tack || !s->tackA || !s->tackB || checkArg(av + 1, s))
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

int checkArg(char *av[], stacks *s)
{
	int i;
	int j;

	while (!(i = 0) && *av)
	{
		if ((*av)[i] == '-' || (*av)[i] == '+')
			if (!(*av)[++i])
				return (1);
		while ((*av)[i])
		{
			if ('0' > (*av)[i] || (*av)[i] > '9')
				return (1);
			++i;
		}
		s->tack[s->sizeA] = putNb(*av);
		s->tackA[s->sizeA++] = putNb(*av);
		++av;
	}
	while (i < s->sizeA) // check les doublons
	{
		j = ++i;
		while (j < s->sizeA)
			if (s->tack[i - 1] == s->tackA[j++])
				return (1);
	}
	return (0);
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
