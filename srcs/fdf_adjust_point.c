/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_adjust_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:49:37 by npiya-is          #+#    #+#             */
/*   Updated: 2022/10/15 23:31:48 by npiya-is         ###   ########.fr       */
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
	value.y = ((1920 / img.depth) / div) * img.zoom;
	value.z = (1080 / ((img.width + img.depth) / 2) / div) * img.zoom;
	return (value);
}

t_point	adjust_with_center(t_point pnt, t_vars vars)
{
	vars.mode = 0;
	pnt.x *= vars.zoom.x;
	pnt.y *= vars.zoom.y;
	pnt.z *= vars.zoom.z;
	pnt.x = pnt.x + vars.center.x;
	pnt.y = pnt.y + vars.center.y;
	pnt.z = pnt.z + vars.center.z;
	return (pnt);
}

t_point	find_center(t_vars vars)
{
	int		i;
	int		j;
	t_point	center;

	i = vars.img.width / 2;
	j = vars.img.depth / 2;
	center.x = 0;
	center.y = 0;
	center.z = 0;
	center = adjust_with_center(center, vars);
	center.x = 980 - vars.zoom.x;
	center.y = 580 - vars.zoom.y;
	center.z = 400 - vars.zoom.z;
	return (center);
}

t_point	offset_point(t_point pnt, t_vars vars)
{
	t_point	offset;

	offset.x = pnt.x - (vars.img.width / 2);
	offset.y = pnt.y - (vars.img.depth / 2);
	offset.z = pnt.z;
	return (offset);
}

t_point	assign_point(t_vars vars, int i, int j)
{
	t_point	pnt;

	pnt = vars.data[i][j].node;
	pnt = offset_point(pnt, vars);
	pnt = point_transformation(pnt, vars);
	pnt = adjust_with_center(pnt, vars);
	return (pnt);
}
