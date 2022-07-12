/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:03:51 by adtheus           #+#    #+#             */
/*   Updated: 2020/11/08 00:31:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl(char *tmp_str)
{
	int rest_pos;

	if (!tmp_str)
		return (0);
	rest_pos = 0;
	while (tmp_str[rest_pos])
		if (tmp_str[rest_pos++] == '\n')
		{
			tmp_str[rest_pos - 1] = '\0';
			return (rest_pos);
		}
	return (0);
}

int		alloc_line(char **line, char *current_line, int len)
{
	char	*str;
	int		i;
	int		j;

	i = ft_strlen((const char *)*line);
	if (!(str = malloc(sizeof(char) * (i + len + 1))))
		return (error);
	j = -1;
	while (++j < i)
		str[j] = (*line)[j];
	i = 0;
	while (i++ < len)
		str[j++] = *current_line++;
	str[j] = '\0';
	free(*line);
	*line = str;
	return (new_line);
}

int		get_next_line(int fd, char **line)
{
	static char	sstr[5000][BUFFER_SIZE + 1];
	int			len;
	int			pos;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (error);
	len = -1;
	*line = NULL;
	while (len && !(pos = gnl(sstr[fd])))
	{
		alloc_line(line, sstr[fd], (len < 0 ? ft_strlen(sstr[fd]) : len));
		if (-1 == (len = read(fd, sstr[fd], BUFFER_SIZE)))
			return (error);
		sstr[fd][len] = '\0';
	}
	alloc_line(line, sstr[fd], pos);
	ft_memmove(sstr[fd], &sstr[fd][pos], (ft_strlen(&sstr[fd][pos]) + 1));
	return ((!len && !(ft_strlen(sstr[fd])) ? end_file : new_line));
}
