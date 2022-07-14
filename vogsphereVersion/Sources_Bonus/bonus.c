/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:26:47 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 17:47:40 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

static void	exec_manip_bonus(t_stacks *s, char **actions)
{
	int		i;
	int		action;
	void	(*func[12])(t_stacks *s);

	i = -1;
	arm_func_array(func);
	func[0](s);
	while (actions && actions[++i])
	{
		action = exec_action(actions[i]);
		if (action == -1)
		{
			panic_error();
		}
		else
			func[action](s);
	}
}

int	main(int ac, char *av[])
{
	t_stacks	s;
	char		*action;
	char		**actions;

	if (ac == 1)
		return (0);
	actions = NULL;
	while (get_next_line(0, &action))
		actions = gnl_2000(actions, action);
	free(action);
	init(--ac, ++av, &s);
	exec_manip_bonus(&s, actions);
	if (is_sorted(s.l_a, s.size_a, e_true))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_strs(actions);
	free(s.action);
	free(s.head_a);
	free(s.tack_sort);
	return (0);
}
