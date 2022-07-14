/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initCheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:26:30 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init(int ac, char *av[], t_stacks *s)
{
	if (!ac)
		exit(277);
	s->tack_sort = malloc(sizeof(int) * ac);
	s->action = malloc(sizeof(int) * 2500);
	ft_bzero(s->action, sizeof(int) * 2500);
	s->l_a = malloc(sizeof(*s->l_a) * ac);
	s->l_b = NULL;
	s->size = 0;
	s->idx_action = 0;
	if (!s->l_a || check_arg(av, s))
		panic_error();
	sort(s->tack_sort, s->size);
	s->head_a = s->l_a;
	ac = -1;
	while (++ac < s->size_a - 1)
	{
		s->l_a[ac].stay = 0;
		s->l_a[ac].idx = get_index(s, s->l_a[ac].data);
		s->l_a[ac].next = &s->l_a[ac + 1];
		s->l_a[ac + 1].prev = &s->l_a[ac];
	}
	s->l_a[ac].stay = 0;
	s->l_a[ac].idx = get_index(s, s->l_a[ac].data);
	s->l_a[s->size_a - 1].next = &s->l_a[0];
	s->l_a[0].prev = &s->l_a[s->size_a - 1];
}

int	check_duplicate(t_stacks *s)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < s->size)
	{
		tmp = s->l_a[i].data;
		j = ++i;
		while (j < s->size)
			if (tmp == s->l_a[j++].data)
				return (1);
	}
	return (0);
}

int	check_arg(char *av[], t_stacks *s)
{
	int	i;

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
		s->tack_sort[s->size] = put_nb(*av);
		s->l_a[s->size].data = s->tack_sort[s->size];
		++s->size;
		++av;
	}
	s->size_a = s->size;
	s->size_b = 0;
	return (check_duplicate(s));
}

int	put_nb(char *str_nb)
{
	long	nb;
	int		sign;

	if (!str_nb || !(*str_nb))
		panic_error();
	sign = 1;
	if (*str_nb == '-' && ++str_nb)
		sign = -1;
	nb = 0;
	while (*str_nb)
	{
		nb *= 10;
		nb += *str_nb++ - '0';
	}
	if (nb > __INT_MAX__ || nb < -2147483648)
		panic_error();
	return (nb * sign);
}

void	sort(int *array, int size)
{
	int	i;
	int	j;
	int	*tmp;
	int	swap;

	i = -1;
	while (++i < size)
	{
		j = i;
		tmp = &array[i];
		while (++j < size)
			if (array[j] < *tmp)
				tmp = &array[j];
		if (tmp != &array[i])
		{
			swap = *tmp;
			*tmp = array[i];
			array[i] = swap;
		}
	}
}
