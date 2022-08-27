/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaewsae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:40:23 by lkaewsae          #+#    #+#             */
/*   Updated: 2022/07/15 02:34:14 by lkaewsae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		free_tmp(char *tmp);

int			ft_strchr(const char *s, char c);

static int	ft_strlen(char *s, int mode)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	if (mode == 0)
	{
		while (s[i] != '\0')
			i++;
	}
	else if (mode == 1)
	{
		while (s[i] != '\0' && s[i] != '\n')
			i++;
		if (s[i] == '\n')
			i++;
	}
	return (i);
}

static char	*keep_string(char *tmp, char *line)
{
	int		i;
	int		tmplen;
	int		linelen;
	char	*keep;

	i = 0;
	tmplen = ft_strlen(tmp, 0);
	linelen = ft_strlen(line, 0);
	keep = malloc((tmplen - linelen) + 1 * sizeof(char));
	if (!keep)
		return (NULL);
	while (tmp != NULL && tmp[linelen + i] != '\0')
	{
		keep[i] = tmp[linelen + i];
		i++;
	}
	free(tmp);
	keep[i] = '\0';
	if (keep[0] == '\0')
	{
		free(keep);
		keep = NULL;
	}
	return (keep);
}

static char	*copy_string(char *tmp)
{
	int		i;
	char	*line;

	i = 0;
	if (tmp == NULL || tmp[i] == '\0' )
		return (NULL);
	line = malloc(ft_strlen(tmp, 1) + 1 * sizeof(char));
	if (!line)
		return (NULL);
	while (tmp != NULL && tmp[i] != '\0' && tmp[i] != '\n')
	{
		line[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else if (tmp[i] == '\0')
		line[i] = '\0';
	return (line);
}

char	*transfer_string(char *tmp, char *buff)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
	i = 0;
	if (!tmp && !buff)
		return (NULL);
	line = malloc(((ft_strlen(tmp, 0) + ft_strlen(buff, 0)) + 1));
	if (line == NULL)
		return (NULL);
	while (tmp != NULL && tmp[i] != '\0')
	{
		line[i] = tmp[i];
		i++;
	}
	while (buff[j] != '\0')
	{
		line[i + j] = buff[j];
		j++;
	}
	line[i + j] = '\0';
	if (tmp != NULL)
		free_tmp(tmp);
	return (line);
}

char	*get_next_line(int fd)
{	
	int			nbyte;
	char		*line;
	char		*buff;
	char		*tmp;
	static char	*keep[OPEN_MAX];

	line = NULL;
	tmp = NULL;
	nbyte = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	tmp = keep[fd];
	while (ft_strchr(tmp, '\n') == 0 && nbyte != 0)
	{	
		nbyte = read(fd, buff, BUFFER_SIZE);
		buff[nbyte] = '\0';
		tmp = transfer_string(tmp, buff);
	}
	free(buff);
	line = copy_string(tmp);
	keep[fd] = keep_string(tmp, line);
	return (line);
}
/*
int	main(int argc, char *argv[])
{
	int fd;
	int i;
	char	*line;

	fd = 0;
	line = NULL;
	i = 1;
	if (argc >= 2)
	{
		while (i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			line = get_next_line(fd);
			while (line)
			{
				printf("%s", line);
				free(line);
				line = get_next_line(fd);
			}
			i++;
		}
	}
	close(fd);
	return (0);
}*/
