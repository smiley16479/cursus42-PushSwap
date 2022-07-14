/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 18:53:03 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 13:28:36 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* int		ft_strlen(const char *str)
{
	int len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
} */

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*original_dest;

	if (!dst && !src)
		return (NULL);
	original_dest = dst;
	while (len--)
	{
		if (src < dst)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
		else
			*((unsigned char *)dst++) = *((unsigned char *)src++);
	}
	return (original_dest);
}
