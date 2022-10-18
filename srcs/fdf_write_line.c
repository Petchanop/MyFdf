/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_write_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 23:57:40 by npiya-is          #+#    #+#             */
/*   Updated: 2022/10/18 20:59:55 by npiya-is         ###   ########.fr       */
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

	i = 1;
	while (i < vars.img.depth)
	{
		j = 1;
		while (j < vars.img.width)
		{
			project3d(vars.data[i - 1][j - 1], vars.data[i - 1][j], vars);
			project3d(vars.data[i][j - 1], vars.data[i - 1][j - 1], vars);
			j++;
		}
		i++;
	}
}

void	project3d(t_map data, t_map data1, t_vars vars)
{
	t_point	begin;
	t_point	diff;
	t_point	step;
	t_point	stop;
	int		color;

	begin = assign_point(vars, data);
	stop = assign_point(vars, data1);
	diff = find_dxdy(begin, stop);
	step.y = diff.y / find_stepxy(diff);
	step.x = diff.x / find_stepxy(diff);
	color = assign_color(data, data1);
	while (check_point(begin, stop, step))
	{
		color = color_gradient(color, data, data1);
		my_mlx_pixel_put(&vars.img, begin.x, begin.y, color);
		begin.y += step.y;
		begin.x += step.x;
	}
}
