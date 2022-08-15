/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:41:13 by npiya-is          #+#    #+#             */
/*   Updated: 2022/03/25 03:30:48 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

typedef struct s_file
{
	char	*stream;
	char	*line;
	size_t	start;
	size_t	newline;
}	t_file;

char	*get_next_line(int fd);
void	*ft_memcpy(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *str);
#endif
