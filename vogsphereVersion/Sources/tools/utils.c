#include "utils.h"

int ft_strlen(const char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (*str++)
		++i;
	return (i);
}

void printList(t_node *l, int size)
{
	for (size_t i = 0; i < size; i++) {
		fprintf(stderr, "prev : %p -> me(%2d) stat %d : %p -> next : %p\n", l->prev, l->data, l->stay, l, l->next);
		// printf("data : %d\n", l[i].data);
		l = l->next;
	}
}

void printStacks(stacks s)
{
	fprintf(stderr, "list A\n");
	printList(s.l_A, s.sizeA);
	fprintf(stderr, "list B\n");
	printList(s.l_B, s.sizeB);
}

void init(int ac, char *av[], stacks *s)
{
	if (!ac)
		exit(277);
	s->tackSort = malloc(sizeof(int) * ac);
	s->action = malloc(sizeof(int) * 2500);
	ft_bzero(s->action, sizeof(int)*2500);
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	printf("%d\n", s->action[i]);
	// }
	
	s->l_A = malloc(sizeof(*s->l_A) * ac);
	s->l_B = NULL;

	s->size = 0;
	s->idxAction = 0;
	if (!s->l_A || checkArg(av, s))
		panicERROR();
	sort(s->tackSort, s->size);
	// printf("ac : %d, size : %d\n", ac, s->size);

	s->head_A = s->l_A;
	ac = -1;
	while (++ac < s->sizeA - 1)
	{
		s->l_A[ac].stay = 0;
		s->l_A[ac].idx = get_index(s, s->l_A[ac].data);
		s->l_A[ac].next = &s->l_A[ac + 1];
		s->l_A[ac + 1].prev = &s->l_A[ac];
	}
	s->l_A[ac].stay = 0;
	s->l_A[ac].idx = get_index(s, s->l_A[ac].data);
	s->l_A[s->sizeA - 1].next = &s->l_A[0];
	s->l_A[0].prev = &s->l_A[s->sizeA - 1];
}

// Changé pour ne tester qu'un interval av des list : Pas testé
int isSorted(t_node *l, int size, int ascending)
{
	int i;

	i = -1;
	if (ascending)
		while (++i < size - 1)
		{
			if (l->data > l->next->data)
				return (0);
			l = l->next;
		}
	else
		while (++i < size - 1)
		{
			if (l->data < l->next->data)
				return (0);
			l = l->next;
		}
	return (1);
}

void writeAction(stacks *s, enum action act)
{
	char *a[] = {
				"", "sa", "sb" ,"ss", "pa",
				"pb","ra", "rb", "rr",
				"rra", "rrb" , "rrr"
				};
	// printf("Write Action %d (%s)\n", s->idxAction, a[act]);

	if (!(s->action[s->idxAction] & 0x0F))
	{
		(s->action[s->idxAction]) = act;
		// printf("w poid faible %d\n", act);
	}
	else if (!(s->action[s->idxAction] & 0xF0))
	{
		// printf("w poid fort (++idx) %d\n");
		s->action[s->idxAction] |= (act << 4);
		// printf("w poid fort (++idx) %d\n", s->action[s->idxAction] >> 4);
		++s->idxAction;
	}
}

void readAction(stacks *s)
{
	int i;
	int j;
	char *a[] = {
				"", "sa\n", "sb" ,"ss\n", "pa\n",
				"pb\n","ra\n", "rb\n", "rr\n",
				"rra\n", "rrb\n", "rrr\n"
				};

	// printf("readAction %d\n", s->idxAction);
	i = -1;
	while (++i <= s->idxAction && s->action[i] && !(j = 0))
	{
		while (++j <= e_rrr)
			if ((s->action[i] & 0x0F) == j)
			{
				write(1, a[j], ft_strlen(a[j]));
				// write(1, "\n", 1);
				// printf(" r poid faible %d (%s)\n", j, a[j]);
			}
		j = 0;
		// printf(" r poid fort %d\n", ((s->action[i] & 0xF0) >> 4));
		while (++j <= e_rrr)
			if (((s->action[i] & 0xF0) >> 4) == j)
			{
				write(1, a[j], ft_strlen(a[j]));
				// write(1, "\n", 1);
				// printf(" r poid fort %d (%s)\n", j, a[j]);
			}
	}
}

int count_n_clear_True(t_node *l, int size)
{
	int i;

	i = 0;
	while (size--)
	{
		if (l->stay && ++i)
			l->stay = e_false;
		l = l->next;
	}
	return (i);
}

void ft_bzero(void *s, int n)
{
	int i;

	i = -1;
	while (++i < n)
		*(char *)s++ = 0;
}

void *ft_memcpy(const void *src, size_t n)
{
	void *dest;
	size_t i;

	if (!(dest = malloc(n)))
		exit(-1);
	i = -1;
	while (++i < n)
		((char*)dest)[i] = ((char*)src)[i];
	return dest;
}

t_node *ft_lstCpy(t_node *l, size_t n)
{
	t_node *to_ret;
	size_t i;

	if (!(to_ret = malloc(n * sizeof(t_node))))
		exit(-1);
	to_ret[n - 1].next = &(to_ret[0]);
	to_ret[0].prev = &(to_ret[n - 1]);
	i = -1;
	while (++i < n)
	{
		to_ret[i].stay = l->stay;
		to_ret[i].data = l->data;
		to_ret[i].idx = l->idx;
// comment fait on pour les extrémitées
		if (i != n - 1)
			to_ret[i].next = &(to_ret[i + 1]);
		if (i != 0)
			to_ret[i].prev = &(to_ret[i - 1]);
		l = l->next;
	}
	return to_ret;
}

#include <string.h>
void test(stacks *s, /* enum action */ char act)
{
	if (act & 0x0F)
	{
		// (act) = act << 4;
		printf("poid faible %d\n", 4 << act);
	}
	if (act & 0xF0)
	{
		printf("poid fort (++idx) %d\n");
	}
}