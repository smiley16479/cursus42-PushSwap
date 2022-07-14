/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:19:48 by adtheus           #+#    #+#             */
/*   Updated: 2022/07/14 14:01:49 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include "utils.h"

enum	e_list
{
	error = -1,
	end_file,
	new_line
};

char				**gnl_2000(char **str_strs, char *str);

int					ft_strlen(const char *str);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					gnl(char *tmp_str);
int					alloc_line(char **line, char *current_line, int len);
int					get_next_line(int fd, char **line);

/* 
** Bonus_utils.c
*/
void				free_strs(char **strs);
int					ft_strcmp(const char *s1, const char *s2);
int					exec_action(char *action);
void				arm_func_array(void (*func[12])(t_stacks *s));

#endif
