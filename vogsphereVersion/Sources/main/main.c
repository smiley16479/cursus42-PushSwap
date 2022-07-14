/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:51:50 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:15:26 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	main(int ac, char *av[])
{
	t_stacks	s;

	init(--ac, ++av, &s);
	gt_sort_swap_further(&s);
	read_action(&s);
	free(s.action);
	free(s.head_a);
	free(s.tack_sort);
	return (0);
}
