/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:49:37 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/15 15:38:541:12 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	point_transformation(t_mapdata dest)//, int width, int height)
{
	t_point	new_point;
	int		zoom;

	zoom = 32;
	new_point.x = (((dest.point.x * cos(0.8944)) - (dest.point.y * sin(0.4472))) * zoom) - dest.value;// * (width / 2);// + dest.value;
	new_point.y = (((dest.point.x * cos(0.8944)) + (dest.point.y * sin(0.4472))) * zoom) - dest.value;// * (height / 2);// - dest.value;
	return (new_point);
}

int	valid_point(t_point point)
{
	if (point.x <= 1920 && point.y <= 1080)
		return (1);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	write_line(t_data img, t_mapdata **data)
{
	int	i;
	int	j;
	t_point	start;
	t_point	end_x0;
	t_point	end_y0;

	i = 1;
	while (i <= img.height)
	{
		j = 1;
		while (j <= img.width)
		{
			start = point_transformation(data[i - 1][j - 1]);//, 32, 32);
			end_x0 = point_transformation(data[i - 1][j]);//, 32, 32);
			if (i < img.height)
				end_y0 = point_transformation(data[i][j - 1]);//, 32, 32);
			//printf("start : %.2f,%.2f\n", start.x, start.y);
			//printf("end   : %.2f,%.2f\n", end.x, end.y);
			if (valid_point(start) && valid_point(end_x0) && valid_point(end_y0))
			{
				write_horizontal_line(start, end_x0, data[i - 1][j], img);
				write_vertical_line(end_y0, start, data[i - 1][j], img);
			}
			else
				break ;
			j++;
		}
		i++;
	}
}

void	write_horizontal_line(t_point start, t_point end, t_mapdata data, t_data img)
{
	t_point	begin;
	int		color;

	begin = start;
	if (!data.color && data.value == 0)
		color = 255;
	else if (!data.color && data.value != 0)
		color = ft_hextoi("0x66ff33");
	else
		color = data.color;
	while (begin.x < end.x && end.x <= 1920 && end.y <= 1080)
	{
		my_mlx_pixel_put(&img, 950 + begin.x, begin.y, color);
		begin.y += 0.5;
		begin.x++;
	}
}

void	write_vertical_line(t_point start, t_point end, t_mapdata data, t_data img)
{
	t_point	begin;
	int		color;

	begin = start;
	if (!data.color && data.value == 0)
		color = 255;
	else if (!data.color && data.value != 0)
		color = ft_hextoi("0x66ff33");
	else
		color = data.color;
	printf("start : %.2f,%.2f\n", start.x, start.y);
	printf("end   : %.2f,%.2f\n", end.x, end.y);
	while (begin.x < end.x && end.x <= 1920 && end.y <= 1080)
	{
		my_mlx_pixel_put(&img, 950 + begin.x, begin.y, color);
		begin.y -= (0.5);
		begin.x++;	
	}
}
