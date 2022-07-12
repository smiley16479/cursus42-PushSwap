#include <utils.h>

/* 
** Pop le bon élément de A vers B en checkant si des swap sont néccessaire à chaque manip de A
*/
void popAB(stacks *s, int idx, int swapInterval)
{
	if (idx == -1) {
		printf("popAB() idx == -1 (popAB non trouvé)\n");
		exit(1);
	}
	if (idx <= s->sizeA / 2)
		while (--idx >= 0)
		{
			// if (check_AB_Swap(s, swapInterval))
			// 	sa(s);
			ra(s);
		}
	else
		while (++idx <= s->sizeA)
		{
			// if (check_AB_Swap(s, swapInterval))
			// 	sa(s);
			rra(s);
		}
	pb(s);
	// check_AB_Swap(s, swapInterval);
}

void sortSimple_3(stacks *s, t_node **l, char stackID)
{
	t_node *n[3] = {*l , (*l)->next, (*l)->next->next};
	int ID = 0;
	if (n[0]->data > n[1]->data && n[0]->data < n[2]->data && (ID = 1))
		swap(*l);
	else if (n[0]->data > n[1]->data && n[1]->data < n[2]->data && (ID = 2))
		rotate(l);
	else if (n[0]->data < n[1]->data && n[0]->data > n[2]->data && (ID = 3))
		revRotate(l);
	else if (n[0]->data > n[1]->data && n[1]->data > n[2]->data && (ID = 4))
	{
		swap(*l);
		revRotate(l);
	}
	else if (n[0]->data < n[1]->data  && n[1]->data > n[2]->data && (ID = 5))
	{
		swap(*l);
		rotate(l);
	}
	// printList(*l, 3);
	if (stackID == 'A' && (ID == 1 || ID == 4 || ID == 5))
		writeAction(s, e_sa);
	if (stackID == 'B' && (ID == 1 || ID == 4 || ID == 5))
		writeAction(s, e_sb);
	if (stackID == 'A' && (ID == 2 || ID == 5))
		writeAction(s, e_ra);
	if (stackID == 'B' && (ID == 2 || ID == 5))
		writeAction(s, e_rb);
	if (stackID == 'A' && (ID == 3 || ID == 4))
		writeAction(s, e_rra);
	if (stackID == 'B' && (ID == 3 || ID == 4))
		writeAction(s, e_rrb);
}

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