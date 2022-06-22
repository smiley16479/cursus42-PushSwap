#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

enum action {empty, e_sa, e_sb ,e_ss, e_pa, e_pb, e_ra, e_rb, e_rr, e_rra, e_rrb , e_rrr};

typedef enum
{
	e_false,
	e_true,
	e_swap1,
	e_swap2,
	e_swapGap1,
	e_swapGap2,
}	t_bool;

typedef struct s_node{
	int	data;
	t_bool stay;
	struct s_node *prev;
	struct s_node *next;
}t_node;

typedef struct stacks{
	int *tackSort;
	char *action;
	t_node *l_A;
	t_node *l_B;
	t_node *head_A;
	int size;
	int sizeA;
	int sizeB;
	int idxAction;

	int chunkSize;
	int chunkIdx;
}stacks;

// utils.c
void printList(t_node *l, int size); // faclutatif
void printStacks(stacks s); // faclutatif
void init(int ac, char *av[], stacks *s);
int isSorted(t_node *l, int size, int ascending);
void writeAction(stacks *s, enum action act);
void readAction(stacks *s);
int count_n_clear_True(t_node *l, int size);
void ft_bzero(void *s, int n);
void *ft_memcpy(const void *src, size_t n);
t_node *ft_lstCpy(t_node *l, size_t n);

// initCheck.c
void panicERROR(void);
int checkDuplicate(stacks *s);
int checkArg(char **av, stacks *s);
int putNb(char *strNb);
void sort(int *array, int size);

// swap.c
void swap(t_node *l_);
void sa(stacks *s);
void sb(stacks *s);
void ss(stacks *s);

// push.c
void pa(stacks *s);
void pb(stacks *s);

// rotat.c
void rotate(t_node **l_);
void ra(stacks *s);
void rb(stacks *s);
void rr(stacks *s);

// revRotat.c
void revRotate(t_node **l_);
void rra(stacks *s);
void rrb(stacks *s);
void rrr(stacks *s);

// chunk.c
void midPointAlgo(stacks *s);

// chunkManip.c
void sortSimple_3(stacks *s, t_node **l, char stackID);

// autoSwapCheck.c
int check_A_Swap(stacks *s);
int check_B_Swap(stacks *s);
int check_AB_Swap(stacks *s);

int *testWithNewConfig(stacks *s, t_node *l);
int elem_to_keep_gtSort_swap(stacks *s);


// suitSort.c
void select_suitSort_pb(stacks *s);
void push_to_B(stacks *s);

// suitSortUtils.c
int get_index(stacks *s, int elem);

// gt_sort.c
int elem_to_keep_gtSort(stacks *s);
long	getMaxFollowedElem(int **arr, int size);
int	getLowestIdx(int *arr, int size);
int followedElem(t_node *l, int size, t_bool markElem);
void isBetterAfterSwap(stacks *s);
int *elem_to_keep_gtSort_swapFurther(stacks *s, int interval, t_bool markElem);


#endif