/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:49:37 by npiya-is          #+#    #+#             */
/*   Updated: 2022/09/03 15:51:58 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	find_proportion(t_data img)
{
	t_point	value;
	float	div;

	if (img.width + img.height <= 50)
		div = 4;
	else
		div = 2;
	value.x = ((1920 / img.width) / div) * img.zoom;
	value.y = ((1080 / img.height) / div) * img.zoom;
	return (value);
}

t_point	find_center(t_vars vars, t_mapdata **data)
{
	int		i;
	int		j;
	t_point	center;

	i = vars.img.width / 2;
	j = vars.img.height / 2;
	center.x = 0;
	center.y = 0;
	center = point_transformation(data[j][i], center, vars.zoom);
	center.x = 960 - center.x;
	center.y = 440 - center.y;
	return (center);
}

t_point	find_dxdy(t_point start, t_point end)
{
	t_point		diff;

	diff.x = (end.x - start.x);
	diff.y = (end.y - start.y);
	return (diff);
}

float	find_step(t_point diff)
{
	if (fabs(diff.x) >= fabs(diff.y))
		return (fabs(diff.x));
	else
		return (fabs(diff.y));
}

t_point	point_transformation(t_mapdata dst, t_point center, t_point zoom)
{
	t_point	point;
	float	value;

	if (dst.value)
		value = dst.value;
	else
		value = 0;
	point.x = (((dst.point.x * cos(0.6)) - (dst.point.y * sin(0.6))) - (value / 5));
	point.y = (((dst.point.x * sin(0.6)) + (dst.point.y * cos(0.6))) - (value / 2));
	point.x *= zoom.x;
	point.y *= zoom.y;
	point.x = point.x + center.x;
	point.y = point.y + center.y;
	return (point);
}

int	valid_point(t_point point)
{
	if (point.x < 1920 && point.y < 1080 && point.x > 0 && point.y > 0)
		return (1);
	return (0);
}