/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:44:18 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/27 15:35:34 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*psrc;
	unsigned char	*pdst;

	psrc = (unsigned char *)src;
	pdst = (unsigned char *)dst;
	if (!dst)
		return (NULL);
	while (len-- && psrc)
		*pdst++ = *psrc++;
	*(pdst - 1) = '\0';
	return (dst);
}

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*str;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	str[i + ft_strlen(s1)] = '\0';
	free(s1);
	return (str);
}

char	*ft_startnline(t_file *ptr)
{
	char	*remaining_str;
	int		i;
	int		j;

	i = ptr->newline;
	j = 0;
	remaining_str = malloc(((ft_strlen(ptr->stream) - ptr->newline) + 1));
	if (remaining_str == NULL)
		return (NULL);
	while (ptr->stream[i])
	{
			remaining_str[j] = ptr->stream[i];
			i++;
			j++;
	}
	remaining_str[j] = '\0';
	free(ptr->stream);
	ptr->newline = 0;
	return (remaining_str);
}
