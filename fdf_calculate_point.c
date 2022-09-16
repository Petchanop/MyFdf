/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_calculate_point.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:23:19 by npiya-is          #+#    #+#             */
/*   Updated: 2022/09/15 02:25:05 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	y_point_transformation(t_map *dst, t_vars vars)
{
	dst->node.x = (dst->node.x * cos(vars.angle)) - (dst->node.z * sin(vars.angle));
	dst->node.z = (dst->node.x * sin(vars.angle)) + (dst->node.z * cos(vars.angle));
	return (dst->node);
}

t_point	x_point_transformation(t_map *dst, t_vars vars)
{
	float	y;

	y = dst->node.y / 2;
	dst->node.z = (dst->node.z * cos(vars.angle)) - (y * sin(vars.angle));
	dst->node.y = (dst->node.z * sin(vars.angle)) + (y * cos(vars.angle));
	return (dst->node);
}

t_point	z_point_transformation(t_map *dst, t_vars vars)
{
	float	y;

	y = dst->node.y / 2;
	dst->node.x = (dst->node.x * cos(vars.angle)) + (dst->node.y * sin(vars.angle));
	dst->node.z = (dst->node.y * cos(vars.angle) - (dst->node.x * sin(vars.angle)));
	return (dst->node);
}

t_point	plot_point(t_map *dst, t_vars vars)
{
	t_point	temp;

	temp.x = dst->node.x;
	temp.y = dst->node.y;
	temp.z = dst->node.z;
	// if (vars.mode == 0)
		temp = y_point_transformation(dst, vars);
	if (vars.mode == 1)
		temp = x_point_transformation(dst, vars);
	if (vars.mode == 2)
		temp = z_point_transformation(dst, vars);
	return (temp);
}
