/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_write_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 23:57:40 by npiya-is          #+#    #+#             */
/*   Updated: 2022/09/03 19:52:19 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	find_dxdy(t_point start, t_point end);

float	find_step(t_point diff);

int		valid_point(t_point point);

int	check_point(t_point begin, t_point end, t_point step)
{
	if (valid_point(end) && valid_point(begin))
	{
		if (step.x > 0)
		{
			if (begin.x < end.x)
				return (1);
		}
		else
		{
			if (begin.x > end.x)
				return (1);
		}
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	write_line(t_vars vars)
{
	int	i;
	int	j;
	t_point	start;
	t_point	end_x0;
	t_point	end_y0;

	i = 1;
	while (i <= vars.img.height)
	{
		j = 1;
		while (j <= vars.img.width)
		{
			start = point_transformation(vars.data[i - 1][j - 1], vars.center, vars.zoom);
			if (j == vars.img.width)
				end_x0 = point_transformation(vars.data[i - 1][j - 1], vars.center, vars.zoom);
			else
				end_x0 = point_transformation(vars.data[i - 1][j], vars.center, vars.zoom);
			if (i < vars.img.height)
				end_y0 = point_transformation(vars.data[i][j - 1], vars.center, vars.zoom);
			else
				end_y0 = point_transformation(vars.data[i - 1][j - 1], vars.center, vars.zoom);
			write_horizontal_line(start, end_x0, vars.data[i - 1][j], vars.img);
			write_vertical_line(start, end_y0, vars.data[i - 1][j - 1], vars.img);
			j++;
		}
	i++;
	}
}

void	write_horizontal_line(t_point start, t_point end, t_mapdata data, t_data img)
{
	t_point	begin;
	t_point	stop;
	t_point	diff;
	t_point	step;
	int		color;

	begin = start;
	stop = end;
	diff = find_dxdy(start, end);
	step.y = diff.y / find_step(diff);
	step.x = diff.x / find_step(diff);
	if (!data.color)// && data.value == 0)
		color = 16777215;
	else
		color = data.color;
	// 	color = 255;
	// else if (!data.color && data.value != 0)
	while (check_point(begin, stop, step))
	{
		my_mlx_pixel_put(&img, begin.x, begin.y, color);
		begin.y += step.y;
		begin.x += step.x;
	}
}

void	write_vertical_line(t_point start, t_point end, t_mapdata data, t_data img)
{
	t_point	begin;
	t_point	diff;
	t_point	step;
	t_point	stop;
	int		color;

	diff = find_dxdy(start, end);
	step.y = diff.y / find_step(diff);
	step.x = diff.x / find_step(diff);
	if (!data.color)// && data.value == 0)
		color = 16777215;
	else
		color = data.color;
	begin = start;
	stop = end;
	// 	color = 255;
	// else if (!data.color && data.value != 0)
	while (check_point(begin, stop, step))
	{
		my_mlx_pixel_put(&img, begin.x, begin.y, color);
		begin.y += step.y;
		begin.x += step.x;
	}
}