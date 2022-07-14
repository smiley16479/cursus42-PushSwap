/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:26:40 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:16:53 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

enum e_action
{
	empty,
	e_sa,
	e_sb,
	e_ss,
	e_pa,
	e_pb,
	e_ra,
	e_rb,
	e_rr,
	e_rra,
	e_rrb,
	e_rrr
};

typedef enum e_bool
{
	e_false,
	e_true,
	e_swap1,
	e_swap2,
	e_swapGap1,
	e_swapGap2,
}	t_bool;

typedef struct s_node{
	int				data;
	int				idx;
	t_bool			stay;
	struct s_node	*prev;
	struct s_node	*next;
}t_node;

typedef struct stacks{
	int		*tack_sort;
	char	*action;
	t_node	*l_a;
	t_node	*l_b;
	t_node	*head_a;
	int		size;
	int		size_a;
	int		size_b;
	int		idx_action;
	int		chunk_size;
	int		chunk_idx;
	t_bool	stat;
	int		min_idx;
	int		max_idx;
	int		interval;
}t_stacks;

typedef struct s_move{
	int	r;
	int	rr;
}t_move;

typedef struct s_moves{
	int		added_move;
	t_move	move[2];
}t_moves;

/* 
** utils.c / utilss.c 
*/
void	printList(t_node *l, int size); // faclutatif
void	printStacks(t_stacks s); // faclutatif
void	init(int ac, char *av[], t_stacks *s);
int		is_sorted(t_node *l, int size, int ascending);
void	write_action(t_stacks *s, enum e_action act);
void	read_action(t_stacks *s);
int		count_n_clear_true(t_node *l, int size);
void	ft_bzero(void *s, int n);
void	*ft_memcpy(const void *src, size_t n);
t_node	*ft_lst_cpy(t_node *l, size_t n);
int		ft_strlen(const char *str);

/*
** initCheck.c
*/
void	panic_error(void);
int		check_duplicate(t_stacks *s);
int		check_arg(char **av, t_stacks *s);
int		put_nb(char *strNb);
void	sort(int *array, int size);

/*
** swap.c
*/
void	swap(t_node *l_);
void	sa(t_stacks *s);
void	sb(t_stacks *s);
void	ss(t_stacks *s);

/*
** push.c
*/
void	pa(t_stacks *s);
void	pb(t_stacks *s);

/*
** rotat.c
*/
void	rotate(t_node **l_);
void	ra(t_stacks *s);
void	rb(t_stacks *s);
void	rr(t_stacks *s);

/*
** revRotat.c
*/
void	rev_rotate(t_node **l_);
void	rra(t_stacks *s);
void	rrb(t_stacks *s);
void	rrr(t_stacks *s);

/*
** chunk.c
*/
void	midPointAlgo(t_stacks *s);
int		chunkCmp(int toCmp, int chunk_size, int *chunkSort, int ascending);

/*
** utils_shared.c
*/
void	pop_ab(t_stacks *s, int idx, int swapInterval);
void	sort_simple_3(t_stacks *s, t_node **l, char stackID);
int		get_index(t_stacks *s, int elem);

/*
** autoSwapCheck.c
*/
int		check_a_swap(t_stacks *s, int interval);
int		check_b_swap(t_stacks *s, int interval);
int		check_ab_swap(t_stacks *s, int interval);
int		*testWithNewConfig(t_stacks *s, t_node *l);
int		elem_to_keep_gtSort_swap(t_stacks *s);

/*
** suitSort.c
*/
void	select_suitSort_pb(t_stacks *s);
void	push_to_B(t_stacks *s);

/*
** gt_sort.c
** int		elem_to_keep_gt_sort(t_stacks *s);
*/
long	get_max_followed_elem(int **arr, int size);
int		get_lowest_idx(int *arr, int size);
int		followed_elem(t_node *l, int size, t_bool markElem);
int		*elem_to_keep_gt_sort_swap_further(t_stacks *s, int interval);
void	gt_sort_swap_further(t_stacks *s);
void	mark_elem2keep_gt_sort_swap_further(t_stacks *s, int idx, int interval);
void	ab_nothin_but_true(t_stacks *s, int trueElem, int swapInterval);
int		nearest_popable_true_ab_gt(t_stacks *s);
int		nearest_inserable_ba_gt(t_stacks *s);

/*
** gt_sort_BA / _BA_2.c
*/
void	exec_manip(t_stacks *s, t_move *move);
int		sort_4or_less_nb(t_stacks *s);
void	align(t_stacks *s);

/*
** gt_sort_BA_2.c
*/
int		exec_rr_s(t_stacks *s, t_move *move);
int		exec_r_s(t_stacks *s, t_move *move);
void	exec_r_rr_norm_de_merde(t_stacks *s, t_move *move);
void	exec_r_rr(t_stacks *s, t_move *move);
void	swap_bf4_push(t_stacks *s);

/*
** radix.c
*/
void	radixAlgo(t_stacks *s);
int		nearestPopableAB_radix(t_stacks *s, int chunk_size, int chunk_idx);

#endif