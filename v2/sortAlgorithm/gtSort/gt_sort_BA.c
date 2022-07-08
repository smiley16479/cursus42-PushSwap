#include "utils.h"

/*
** Ajoute (ou soustrait (rr)) les move requis par stack A et B
*/
int calculAddedMove(stacks *s, t_move *move)
{
	if (move[1].r && move[0].r)
	{
		// fprintf(stderr, "added (1) [0].r %d [0].rr %d [1].r %d [1].rr %d \n\n", move[0].r , move[0].rr, move[1].r , move[1].rr)
		if (move[1].r > move[0].r)
			return move[1].r;
		else
			return move[0].r;
	}
	else if (move[1].rr && move[0].rr)
	{
		// fprintf(stderr, "added (2) [0].r %d [0].rr %d [1].r %d [1].rr %d \n\n", move[0].r , move[0].rr, move[1].r , move[1].rr)
		if (move[1].rr > move[0].rr)
			return move[1].rr;
		else
			return move[0].rr;
	}
	else 
	{
		// fprintf(stderr, "added (3) [0].r %d [0].rr %d [1].r %d [1].rr %d \n\n", move[0].r , move[0].rr, move[1].r , move[1].rr);
		return (move[0].r + move[0].rr + move[1].r + move[1].rr);
	} 
}

static inline int isBetween(t_node *l_a, int idx)
{
	if (l_a->prev->idx < idx && idx < l_a->idx)
		return (1);
	return (0);
}

void calcul_A_move(stacks *s, t_move *move, t_node *l_b)
{
	int i;
	t_node *l_a;

	i = 0;
	l_a = s->l_A;
	while (!isBetween(l_a, l_b->idx) && i < s->sizeA)
	{
		l_a = l_a->next;
		++i;
	}
	if (!isBetween(l_a, l_b->idx) && i == s->sizeA) // pour test : peut-être enlevé
	{
		// fprintf(stderr, "On the edge l_b->idx : %d\n", l_b->idx); // pour test : peut-être enlevé
		i = -1;
		while (++i < s->sizeA)
			if (l_a->idx == s->minIdx)
				break ;
			else
				l_a = l_a->next;
	}
	// else
	// 	fprintf(stderr, "OK (i : %d) l_b->idx : %d\n", i, l_b->idx); // pour test : peut-être enlevé 
	if (i <= s->sizeA / 2)
		move->r = i;
	else
		move->rr = s->sizeA - i;
}

/*
** *arr contient le nombre de mouvement à effectuer par index de l_b[i], getLowestValue
** retourne l'index min où le nombre de mouvement à effectuer est le plus petit
*/
int	getLowestValueIdx(t_moves *arr, int size)
{
	int index;
	int i;

	i = 0;
	index = 0;
	while(++i < size)
		if (arr[i].addedMove < arr[index].addedMove)
			index = i;
	// fprintf(stderr, "index av le moins de mvt : arr[%d] : %d\n", index, arr[index].addedMove);
	// for (size_t i = 0; i < size; i++)
	// 	fprintf(stderr, "arr[%d]: %d\n", i, arr[i].addedMove);
	return index;
}

int execRRs(stacks *s, t_move *move)
{
	check_AB_Swap(s, s->interval);
	if (move[0].rr && move[1].rr)
	{
		while (move[0].rr && move[1].rr)
		{
			--move[1].rr;
			--move[0].rr;
			rrr(s);
			check_AB_Swap(s, s->interval);
		}
/* 		while (move[0].rr)
		{
			rra(s);
			--move[0].rr;
			check_AB_Swap(s, s->interval);
		}
		while (move[1].rr)
		{
			rrb(s);
			--move[1].rr;
			check_AB_Swap(s, s->interval);
		}
		return (1); */
	}
	return (0);
}

int execRs(stacks *s, t_move *move)
{
	check_AB_Swap(s, s->interval);
	if (move[0].r && move[1].r)
	{
		while (move[0].r && move[1].r)
		{
			--move[1].r;
			--move[0].r;
			rr(s);
			// if (check_A_Swap(s, s->interval) && move[0].r == 1)
			// 	--move[0].r;
			// if (check_B_Swap(s, s->interval) && move[1].r == 1)
			// 	--move[1].r;
			check_AB_Swap(s, s->interval);
		}
/* 		while (move[0].r)
		{
			ra(s);
			--move[0].r;
			check_AB_Swap(s, s->interval);
		}
		while (move[1].r)
		{
			rb(s);
			--move[1].r;
			check_AB_Swap(s, s->interval);
		}
		return (1); */
	}
	return (0);
}

void execR_RR(stacks *s, t_move *move)
{
	check_AB_Swap(s, s->interval);
	fprintf(stderr, "(execR_RR) l_a.idx : %d, l_a.idx->next : %d\n", s->l_A->idx, s->l_A->next->idx);
	while (move[0].r || move[0].rr || move[1].r || move[1].rr)
	{
		if (move[0].r)
		{
			--move[0].r;
			ra(s);
		}
		if (move[0].rr)
		{
			rra(s);
			--move[0].rr;
		}
		if (move[1].r)
		{
			rb(s);
			--move[1].r;
		}
		if (move[1].rr)
		{
			rrb(s);
			--move[1].rr;
		}
		if (check_A_Swap(s, s->interval) && s->l_A->stay && move[0].r == 1)
			--move[0].r;
		if (check_B_Swap(s, s->interval) && s->l_B->stay && move[1].r == 1)
			--move[1].r;
		check_AB_Swap(s, s->interval);
	}
}

void swap_Bf4_Push(stacks *s)
{
	fprintf(stderr, "swap_Bf4_Push interval : %d\n", s->interval);
	check_AB_Swap(s, s->interval);
	rra(s);
	check_AB_Swap(s, s->interval);
	if (s->l_A->prev->stay >= 2)
		rra(s);
	check_AB_Swap(s, s->interval);
	// ra(s);
}

void execManip(stacks *s, t_move *move)
{
	fprintf(stderr, "(execManip) move[0].r %d move[0].rr %d : move[1].r %d move[1].rr %d \n", move[0].r, move[0].rr, move[1].r, move[1].rr);
	execRs(s, move);
	execRRs(s, move);
	// fprintf(stderr, "execR_RR(s, move)\n");
	execR_RR(s, move);
	if (s->l_A->prev->stay >= 2 /* && (s->l_A->idx < s->l_A->prev->idx
		|| s->l_A->idx < s->l_A->prev->prev->idx)
		&& s->l_A->prev->idx - s->l_A->idx <= s->interval */)
		swap_Bf4_Push(s);
	else
		pa(s);
	printList(s->l_A, s->sizeA);
}

int nearestInserableBA_gt(stacks *s)
{
	int i;
	t_node *l_b;
	t_moves *tab;

	if (!(tab = malloc(sizeof(*tab) * s->sizeB)))
		panicERROR();
	ft_bzero(tab, sizeof(*tab) * s->sizeB);
	i = -1;
	l_b = s->l_B;
	while (++i < s->sizeB)
	{
		if (i <= s->sizeB / 2)
			tab[i].move[1].r = i;
		else
			tab[i].move[1].rr = s->sizeB - i;
		calcul_A_move(s, tab[i].move, l_b);
		tab[i].addedMove = calculAddedMove(s, tab[i].move);
		l_b = l_b->next;
	}
	i = getLowestValueIdx(tab, s->sizeB);
	execManip(s, tab[i].move);
	free(tab);
	return (0);
}
