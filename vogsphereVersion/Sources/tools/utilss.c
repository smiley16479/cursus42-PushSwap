/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilss.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:45:37 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:19:00 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str++)
		++i;
	return (i);
}

void	panic_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

// Changé pour ne tester qu'un interval av des list : Pas testé
int	is_sorted(t_node *l, int size, int ascending)
{
	int	i;

	i = -1;
	if (ascending)
	{
		while (++i < size - 1)
		{
			if (l->data > l->next->data)
				return (0);
			l = l->next;
		}
	}
	else
	{
		while (++i < size - 1)
		{
			if (l->data < l->next->data)
				return (0);
			l = l->next;
		}
	}
	return (1);
}

void	ft_bzero(void *s, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		*(char *)s++ = 0;
}

void	*ft_memcpy(const void *src, size_t n)
{
	void	*dest;
	size_t	i;

	dest = malloc(n);
	if (!dest)
		exit(-1);
	i = -1;
	while (++i < n)
		((char *) dest)[i] = ((char *) src)[i];
	return (dest);
}
