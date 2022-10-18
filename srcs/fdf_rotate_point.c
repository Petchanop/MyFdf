/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:23:19 by npiya-is          #+#    #+#             */
/*   Updated: 2022/10/16 21:07:50 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	rotatez(t_point pnt, t_vars vars)
{
	t_point	pre;

	pre = pnt;
	pnt.x = (pre.x * cos(vars.angle2)) + (pre.y * sin(vars.angle2));
	pnt.y = (pre.y * cos(vars.angle2)) - (pre.x * sin(vars.angle2));
	return (pnt);
}

t_point	rotatex(t_point pnt, t_vars vars)
{
	t_point	pre;

	pre = pnt;
	pnt.x = (pre.x * cos(vars.angle)) - (pre.z * sin(vars.angle));
	pnt.z = (pre.z * cos(vars.angle)) + (pre.x * sin(vars.angle));
	return (pnt);
}

t_point	rotatey(t_point pnt, t_vars vars)
{
	t_point	pre;

	pre = pnt;
	pnt.z = (pre.z * cos(vars.angle1)) - (pre.y * sin(vars.angle1));
	pnt.y = (pre.y * cos(vars.angle1)) + (pre.z * sin(vars.angle1));
	return (pnt);
}

t_point	point_transformation(t_point pnt, t_vars vars)
{
	t_point	pre;

	pre = pnt;
	pre.z *= 0.4;
	pnt = rotatez(pre, vars);
	pnt = rotatex(pnt, vars);
	pnt = rotatey(pnt, vars);
	return (pnt);
}
