/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:49:37 by npiya-is          #+#    #+#             */
/*   Updated: 2022/09/15 19:39:03 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	find_proportion(t_data img)
{
	t_point	value;
	float	div;

	if (img.width + img.depth <= 50)
		div = 4;
	else
		div = 2;
	value.x = ((1920 / img.width) / div) * img.zoom;
	value.y = ((1080 / img.depth) / div) * img.zoom;
	value.z = ((2202 / img.width) / div) * img.zoom;
	printf("%.2f\n", img.zoom);
	printf("%.2f %.2f %.2f\n", value.x, value.y, value.z);
	return (value);
}

t_point	adjust_point(t_point pnt, t_vars vars)
{
	vars.mode = 0;
	pnt.x *= vars.zoom.x;
	pnt.y *= vars.zoom.y;
	pnt.z *= vars.zoom.z;
	pnt.x = pnt.x + vars.center.x;
	pnt.y = -(pnt.y) + vars.center.y;
	pnt.z = pnt.z + vars.center.z;
	//printf("%.2f %.2f %.2f\n", pnt.x, pnt.y, pnt.z);
	return (pnt);
}

t_point	find_center(t_vars vars, t_map **data)
{
	int		i;
	int		j;
	t_point	center;

	i = vars.img.width / 2;
	j = vars.img.depth / 2;
	center.x = 0;
	center.y = 0;
	center.z = 0;
	center = y_point_transformation(&data[j][i], vars);
	center = adjust_point(center, vars);
	center.x = 960 - center.x;
	center.y = 440 - center.y;
	center.z = 440 - center.z;
	printf("%.2f %.2f %.2f\n", center.x, center.y, center.z);
	return (center);
}

t_point	find_dxdy(t_point start, t_point end)
{
	t_point		diff;

	diff.x = (end.x - start.x);
	diff.y = (end.y - start.y);
	diff.z = (end.z - start.z);
	return (diff);
}

float	find_stepxy(t_point diff)
{
	if (fabs(diff.x) >= fabs(diff.y))
		return (fabs(diff.x));
	else
		return (fabs(diff.y));
}

float	find_stepxz(t_point diff)
{
	if (fabs(diff.x) >= fabs(diff.z))
		return (fabs(diff.x));
	else
		return (fabs(diff.z));
}

int	valid_point(t_point point)
{
	if (point.x < 1920 && point.y < 1080 && point.z < 1080)  
	{	
		if (point.x > 0 && point.y > 0 && point.z > 0)
			return (1);
	}
	return (0);
}

t_point	assign_point_x(t_vars vars, int i, int j)
{
	t_point	pnt;

	if (i < vars.img.depth)
	{
		pnt = plot_point(&vars.data[i][j - 1], vars);
		return (adjust_point(pnt, vars));
	}
	else
	{
		pnt = plot_point(&vars.data[i - 1][j - 1], vars);
		return (adjust_point(pnt, vars));
	}
}

t_point	assign_point_x1(t_vars vars, int i, int j)
{
	t_point	pnt;

	if (j == vars.img.width)
	{
		pnt = plot_point(&vars.data[i - 1][j - 1], vars);
		return (adjust_point(pnt, vars));
	}
	else
	{
		pnt = plot_point(&vars.data[i - 1][j], vars);
		return (adjust_point(pnt, vars));
	}
}
