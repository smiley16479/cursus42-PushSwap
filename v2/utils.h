#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

enum action {empty, e_sa, e_sb ,e_ss, e_pa, e_pb, e_ra, e_rb, e_rr, e_rra, e_rrb , e_rrr};

typedef struct s_node{
	int	data;
	struct s_node *prev;
	struct s_node *next;
}t_node;

typedef struct stacks{
	int *tack;
	int *tackSort;
	char *action;
	t_node *l_A;
	t_node *l_B;
	t_node *to_free;
	int size;
	int sizeA;
	int sizeB;
	int idxAction;
}stacks;

// utils.c
void panicERROR(void);
void printList(t_node *l, int size); // faclutatif
int checkArg(char **av, stacks *s);
void init(int ac, char *av[], stacks *s);
int putNb(char *strNb);
void sort(int *array, int size);
int isSorted(t_node *l, int size, int ascending);
void writeAction(stacks *s, enum action act);
void readAction(stacks *s);
void ft_bzero(void *s, int n);

// swap.c
void sa(stacks *s);
void sb(stacks *s);
void ss(stacks *s);

// push.c
void pa(stacks *s);
void pb(stacks *s);

// rotat.c
void ra(stacks *s);
void rb(stacks *s);
void rr(stacks *s);

// revRotat.c
void rra(stacks *s);
void rrb(stacks *s);
void rrr(stacks *s);

// chunk.c
void midPointAlgo(stacks *s);

// autoSwapCheck
int check_A_Swap(stacks *s);
int check_B_Swap(stacks *s);
int check_AB_Swap(stacks *s);

#endif