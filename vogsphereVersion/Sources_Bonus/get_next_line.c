/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:03:51 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 15:58:58 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl(char *tmp_str)
{
	int	rest_pos;

	if (!tmp_str)
		return (0);
	rest_pos = 0;
	while (tmp_str[rest_pos])
	{
		if (tmp_str[rest_pos++] == '\n')
		{
			tmp_str[rest_pos - 1] = '\0';
			return (rest_pos);
		}
	}
	return (0);
}

int	alloc_line(char **line, char *current_line, int len)
{
	char	*str;
	int		i;
	int		j;

	i = ft_strlen((const char *)*line);
	str = malloc(sizeof(char) * (i + len + 1));
	if (!str)
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

void	love_the_norm(char **line, int *len)
{
	*len = -1;
	*line = NULL;
}

int	get_next_line(int fd, char **line)
{
	static char	sstr[5000][BUFFER_SIZE + 1];
	int			len;
	int			pos;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (error);
	love_the_norm(line, &len);
	pos = gnl(sstr[fd]);
	while (len && !pos)
	{
		if (len < 0)
			alloc_line(line, sstr[fd], ft_strlen(sstr[fd]));
		else
			alloc_line(line, sstr[fd], len);
		len = read(fd, sstr[fd], BUFFER_SIZE);
		if (len == -1)
			return (error);
		sstr[fd][len] = '\0';
		pos = gnl(sstr[fd]);
	}
	alloc_line(line, sstr[fd], pos);
	ft_memmove(sstr[fd], &sstr[fd][pos], (ft_strlen(&sstr[fd][pos]) + 1));
	if (!len && !ft_strlen(sstr[fd]))
		return (end_file);
	return (new_line);
}
