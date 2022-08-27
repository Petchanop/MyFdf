/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:50:12 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/27 21:19:28 by npiya-is         ###   ########.fr       */
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
		if (data[i] != ' ')
			width++;
		while (data[i] != ' ' && data[i] && data[i] != '\n')
			i++;
		if (data[i] == '\n')
			break ;
	}
	return (width);
}

t_mapdata	**ft_create_data(t_data *img, char *data)
{
	t_mapdata	**new_data;
	char		**line_split_space;
	char		*buff;
	int			i;
	int			j;
	int			fd;

	new_data = malloc((img->height + 1) * sizeof(t_mapdata *));
	fd = open(data, O_RDONLY);
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
			new_data[i][j].value = ft_atoi(line_split_space[j]);
			new_data[i][j].point.x = j; 
			new_data[i][j].point.y = i; 
			if (ft_strchr(line_split_space[j], ','))
				new_data[i][j].color = ft_hextoi(ft_strchr(line_split_space[j], ','));
			else
				new_data[i][j].color = 0;
			j++;
		}
		free(buff);
		i++;
	}
	close(fd);
	ft_clear_allocate_data(line_split_space);
	return (new_data);
}

void	ft_clear_allocate_data(char **line_split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line_split[j])
		free(line_split[j++]);
	free(line_split);
}