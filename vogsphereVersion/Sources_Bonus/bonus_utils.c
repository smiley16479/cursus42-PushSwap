/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:08 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 15:38:44 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_strs(char **strs)
{
	char	**to_free;

	to_free = strs;
	if (!strs)
		return ;
	while (*strs)
	{
		free(*strs);
		++strs;
	}
	free(to_free);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		++s1;
		++s2;
	}
	return ((unsigned)*s1 - (unsigned)*s2);
}

int	exec_action(char *action)
{
	int		i;
	char	*a[13];

	a[0] = "";
	a[1] = "sa";
	a[2] = "sb";
	a[3] = "ss";
	a[4] = "pa";
	a[5] = "pb";
	a[6] = "ra";
	a[7] = "rb";
	a[8] = "rr";
	a[9] = "rra";
	a[10] = "rrb";
	a[11] = "rrr";
	a[12] = NULL;
	i = -1;
	while (a[++i])
		if (!ft_strcmp(a[i], action))
			return (i);
	return (-1);
}

static inline void	is_last_ptr(t_stacks *s)
{
	(void)s;
}

void	arm_func_array(void (*func[12])(t_stacks *s))
{
	func[0] = is_last_ptr;
	func[1] = sa;
	func[2] = sb;
	func[3] = ss;
	func[4] = pa;
	func[5] = pb;
	func[6] = ra;
	func[7] = rb;
	func[8] = rr;
	func[9] = rra;
	func[10] = rrb;
	func[11] = rrr;
}
