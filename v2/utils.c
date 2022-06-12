#include "utils.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str++)
		++i;
	return (i);
}

void printList(t_node *l, int size)
{
	for (size_t i = 0; i < size; i++) {
		printf("prev : %p -> me(%d) : %p -> next : %p\n", l->prev, l->data, l, l->next);
		// printf("data : %d\n", l[i].data);
		l = l->next;
	}
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
				"", "sa", "sb" ,"ss", "pa",
				"pb","ra", "rb", "rr",
				"rra", "rrb" , "rrr"
				};

	// printf("readAction %d\n", s->idxAction);
	i = -1;
	while (++i <= s->idxAction && s->action[i] && !(j = 0))
	{
		while (++j <= e_rrr)
			if ((s->action[i] & 0x0F) == j)
			{
				write(1, a[j], ft_strlen(a[j]));
				// printf(" r poid faible %d (%s)\n", j, a[j]);
			}
		j = 0;
		write(1, "\n", 1);
		// printf(" r poid fort %d\n", ((s->action[i] & 0xF0) >> 4));
		while (++j <= e_rrr)
			if (((s->action[i] & 0xF0) >> 4) == j)
			{
				write(1, a[j], ft_strlen(a[j]));
				// printf(" r poid fort %d (%s)\n", j, a[j]);
			}
		write(1, "\n", 1);
	}
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

/* 
int main()
{
	int n = 1;
	if(*(char *)&n == 1) {printf("little endian if true; sizeof(enum action)  %d\n", sizeof(enum action));}
	stacks s;
	memset(&s, 0, sizeof(s));
	s.action = malloc(100);
	memset(s.action, 0, 100);
	test(&s, e_sa);
	test(&s, e_sb);
	test(&s, e_sa);
	test(&s, e_sb);
	test(&s, e_sa);
	test(&s, e_sb);
	test(&s, e_sa);
	test(&s, e_sb);

	for (size_t i = 0; i < 10; i++)
	{
		printf("s.action[%d] : %d\n", i, s.action[i]);
	}
	
	// int tab[10] = {9,-1, -18, 8, 17, 164, 7, 18, 54, 6};
	// sort(tab, 10);
	// for (size_t i = 0; i < 10; i++)
	// 	printf("%d\n", tab[i]);
	// writeAction(&s, e_sa);
	// writeAction(&s, e_sa);
	// writeAction(&s, e_sb);
	// writeAction(&s, e_sb);
	// writeAction(&s, e_ss);
	// writeAction(&s, e_ss);
	// writeAction(&s, e_ra);
	// writeAction(&s, e_ra);
	// writeAction(&s, e_rb);
	// writeAction(&s, e_rb);
	// writeAction(&s, e_rr);
	// writeAction(&s, e_rr);
	// writeAction(&s, e_rra);
	// writeAction(&s, e_rra);
	// writeAction(&s, e_rrb);
	// writeAction(&s, e_rrb);
	// writeAction(&s, e_rrr);
	// writeAction(&s, e_rrr);
	// readAction(&s);
	// test(NULL, e_sb);
	// writeAction(NULL, 16);
	return 0;
}
 */