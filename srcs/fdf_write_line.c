/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_write_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 23:57:40 by npiya-is          #+#    #+#             */
/*   Updated: 2022/10/15 23:28:12 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	t_point	x1;
	t_point	x2;

	i = 1;
	while (i < vars.img.depth)
	{
		j = 1;
		while (j < vars.img.width)
		{
			x = assign_point(vars, i - 1, j - 1);
			x1 = assign_point(vars, i - 1, j);
			x2 = assign_point(vars, i, j - 1);
			project3d(x, x1, vars.data[i - 1][j - 1], vars.img);
			project3d(x2, x, vars.data[i - 1][j - 1], vars.img);
			j++;
		}
		i++;
	}
}

void	project3d(t_point start, t_point end, t_map data, t_data img)
{
	t_point	begin;
	t_point	diff;
	t_point	step;
	t_point	stop;
	int		color;

	diff = find_dxdy(start, end);
	step.y = diff.y / find_stepxy(diff);
	step.x = diff.x / find_stepxy(diff);
	if (!data.color && !data.node.z)
		color = 0x555555;
	else if (!data.color && data.node.z)
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
