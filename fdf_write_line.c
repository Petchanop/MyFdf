/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_write_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 23:57:40 by npiya-is          #+#    #+#             */
/*   Updated: 2022/09/15 19:45:38 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	find_dxdy(t_point start, t_point end);

float	find_stepxy(t_point diff);

float	find_stepxz(t_point diff);

int		valid_point(t_point point);

t_point	assign_point_x(t_vars vars, int i, int j);

t_point	assign_point_x1(t_vars vars, int i, int j);

int	check_point(t_point begin, t_point end, t_point step)
{
	if (valid_point(begin))
	{
		if (step.x > 0)
		{
			if (begin.x < end.x)
				return (1);
		}
		else if (step.x < 0)
		{
			if (begin.x > end.x)
				return (1);
		}
		else if (step.y > 0)
		{
			if (begin.y < end.y)
				return (1);
		}
		else if (step.y < 0)
		{
			if (begin.y > end.y)
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
	int		i;
	int		j;
	t_point	x;
	t_point	z;

	i = 1;
	while (i <= vars.img.depth)
	{
		j = 1;
		while (j <= vars.img.width && j < 11)
		{
			z = vars.data[i - 1][j].node;
			z = adjust_point(z, vars);
			x = vars.data[i - 1][j - 1].node;
			x = adjust_point(x, vars);
			//printf("z : %.2f %.2f %.2f\n", z.x, z.y, z.z);
			printf("x : %.2f %.2f %.2f\n", x.x, x.y, x.z);
			if (z.z < 1080 && z.x < 1920 && x.x < 1920 && x.z < 1080 && x.x > 0)
			{
				//my_mlx_pixel_put(&vars.img, z.x, z.z, 255);
				my_mlx_pixel_put(&vars.img, x.x, x.z, 255);
				//my_mlx_pixel_put(&vars.img, x.x, x.y, 16777215);
			}
			//write_horizontal(x, z, vars.data[i - 1][j - 1], vars.img);
			//write_vertical(x, z, vars.data[i - 1][j - 1], vars.img);
			j++;
		}
	i++;
	}
}

void	write_horizontal(t_point start, t_point end, t_map data, t_data img)
{
	t_point	begin;
	t_point	stop;
	t_point	diff;
	t_point	step;
	int		color;

	begin = start;
	stop = end;
	diff = find_dxdy(start, end);
	step.z = diff.z / find_stepxz(diff);
	step.x = diff.x / find_stepxz(diff);
	//printf("step : %.2f %.2f\n", step.x, step.z);
	if (!data.color && !data.node.y)
		color = 16777215;
	else if (!data.color && step.y >= 1)
		color = 255;
	else
		color = data.color;
	while (check_point(begin, stop, step))
	{
		//printf("begin : %.2f %.2f\n", begin.x, begin.z);
		my_mlx_pixel_put(&img, begin.x, begin.z, color);
		begin.z += step.z;
		begin.x += step.x;
	}
}

void	write_vertical(t_point start, t_point end, t_map data, t_data img)
{
	t_point	begin;
	t_point	diff;
	t_point	step;
	t_point	stop;
	int		color;

	diff = find_dxdy(start, end);
	step.y = diff.y / find_stepxy(diff);
	step.x = diff.x / find_stepxy(diff);
	if (!data.color && !data.node.y)
		color = 0x555555;
	else if (!data.color && (step.y < step.x || data.node.y))
		color = 255;
	else
		color = data.color;
	begin = start;
	stop = end;
	while (check_point(begin, stop, step))
	{
		my_mlx_pixel_put(&img, begin.x, begin.y, color);
		begin.y += step.y;
		begin.x += step.x;
	}
}
