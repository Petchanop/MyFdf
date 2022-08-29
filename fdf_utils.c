/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:49:37 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/29 23:55:47 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	find_dxdy(t_point start, t_point end)
{
	t_point		diff;

	diff.x = end.x - start.x;
	diff.y = end.y - start.y;
	return (diff);
}

float	find_step(t_point diff)
{
	if (diff.x >= diff.y)
		return (diff.x);
	else
		return (diff.y);
}

t_point	point_transformation(t_mapdata dst)//, int width, int height)
{
	t_point	point;
	int		zoom;
	float	value;

	zoom = 32;
	if (dst.value)
		value = dst.value;
	else
		value = 0;
	// point.x = (dst.point.x - dst.point.y) * cos(7 * Pi / 6) * zoom;
	// point.y = (dst.point.x + dst.point.y - dst.value) * sin(11 * Pi / 6) * zoom;
	point.x = ((dst.point.x * cos(0.4)) - (dst.point.y * sin(0.4))); // - (value / 4)) 
	point.y = ((dst.point.x * sin(0.4)) + (dst.point.y * cos(0.4))); // - (value / 2)) 
	point.x *= zoom;
	point.y *= zoom;
	return (point);
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
	while (i < img.height)// && i < 5)
	{
		j = 1;
		while (j < img.width)
		{
			start = point_transformation(data[i - 1][j - 1]);//, 32, 32);
			if (j == img.width)
				end_x0 = point_transformation(data[i - 1][j - 1]);	
			else
				end_x0 = point_transformation(data[i - 1][j]);//, 32, 32);
			if (i < img.height)
				end_y0 = point_transformation(data[i][j - 1]);//, 32, 32);
			else
				end_y0 = point_transformation(data[i - 1][j - 1]);	
			if (valid_point(start) && valid_point(end_x0) && valid_point(end_y0))
			{
				//printf("start   : %d,%d %.2f,%.2f\n", i - 1, j - 1, start.x, start.y);
				//printf("end_x0  : %d,%d\n", i - 1, j);
				//my_mlx_pixel_put(&img, 1000 + start.x, start.y, 255);
				//my_mlx_pixel_put(&img, 1000 + end_x0.x, end_x0.y, 0x66ff33);
				//my_mlx_pixel_put(&img, 1000 + end_y0.x, end_y0.y, 0xFFFF00);
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
	t_point	diff;
	int		color;
	int		i;

	begin = start;
	diff = find_dxdy(start, end);
	i = 0;
	if (!data.color && data.value == 0)
		color = 255;
	else if (!data.color && data.value != 0)
		color = ft_hextoi("0x66ff33");
	else
		color = data.color;
	while (begin.y < end.y && end.x <= 1920 && end.y <= 1080)
	{
		my_mlx_pixel_put(&img, 950 + begin.x, 300 + begin.y, color);
		begin.y += (diff.y / find_step(diff));
		begin.x += (diff.x / find_step(diff));
		i++;
	}
}

void	write_vertical_line(t_point start, t_point end, t_mapdata data, t_data img)
{
	t_point	begin;
	t_point	diff;
	int		color;
	int		i;

	begin = start;
	diff = find_dxdy(start, end);
	printf("step  : %.2f\n", find_step(diff));
	printf("start : %.2f %.2f\n", start.x, start.y);
	printf("end   : %.2f %.2f\n", end.x, end.y);
	i = 0;
	if (!data.color && data.value == 0)
		color = 255;
	else if (!data.color && data.value != 0)
		color = ft_hextoi("0x66ff33");
	else
		color = data.color;
	while ((begin.x < end.x) && end.x <= 1920 && end.y <= 1080)
	{
		my_mlx_pixel_put(&img, 950 + begin.x, 300 + begin.y, color);
		begin.y += (diff.y / find_step(diff));
		begin.x += (diff.x / find_step(diff));
		i++;
	}
}
