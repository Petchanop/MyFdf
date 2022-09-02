/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:50:12 by npiya-is          #+#    #+#             */
/*   Updated: 2022/09/02 20:04:22 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_data(char *argv, t_data *img)
{
	char	*buff;
	int		height;
	int		width;
	int		fd;

	fd = open(argv, O_RDONLY);
	height = 0;
	buff = get_next_line(fd);
	width = get_width(buff);
	while (buff)
	{
		free(buff);
		buff = get_next_line(fd);
		height++;
	}
	build_image(img, width, height);
	free(buff);
	close(fd);
}

void	assign_data(char *line, int tilex, int tiley, t_mapdata *data)
{
	char	*str;

	str = ft_strchr(line, ',');
	data->value = ft_atoi(line);
	data->point.x = tilex;
	data->point.y = tiley;
	if (str)
		data->color = ft_hextoi(str);
	else
		data->color = 0;
	free(line);
}

int	get_width(char *data)
{
	int		i;
	int		width;

	i = 0;
	width = 0;
	while (data[i] != '\n' && data[i])
	{
		while (data[i] == ' ' && data[i])
			i++;
		if (data[i] != ' ' && data[i] != '\n')
			width++;
		while (data[i] != ' ' && data[i] && data[i] != '\n')
			i++;
		if (data[i] == '\n')
			break ;
	}
	return (width);
}

t_mapdata	**ft_create_data(t_data *img, int fd)
{
	t_mapdata	**new_data;
	char		**line_split_space;
	char		*buff;
	int			i;
	int			j;

	new_data = malloc((img->height + 1) * sizeof(t_mapdata *));
	buff = "1";
	i = 0;
	while (i < img->height)
	{
		buff = get_next_line(fd);
		line_split_space = ft_split(buff, ' ');
		new_data[i] = malloc((img->width + 1) * sizeof(t_mapdata));
		j = 0;
		while (line_split_space[j])
		{
			assign_data(line_split_space[j], j, i, &new_data[i][j]);
			j++;
		}
		free(buff);
		free(line_split_space);
		i++;
	}
	return (new_data);
}