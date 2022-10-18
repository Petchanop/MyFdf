/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_assign_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:11:40 by npiya-is          #+#    #+#             */
/*   Updated: 2022/10/18 21:00:27 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	assign_color(t_map data, t_map data1)
{
	int	color;

	color = 0;
	if (!data.color && (!data.node.z && !data1.node.z))
		color = 0x555555;
	else if (!data.color && (data1.node.z || data.node.z))
		color = 100;
	else
		color = data.color;
	return (color);
}

int	color_gradient(int color, t_map data, t_map data1)
{
	static int	gradient = 1;

	if (!data.color && color != 0x555555 && (data.node.z || data1.node.z))
	{
		if (color <= 65535)
			color *= (255 - gradient);
		else if (color <= 16777215 && color > 65535)
			color -= (255 - (color / 2)) *(255 - (color / 2));
		gradient++;
	}
	if (gradient == 256)
		gradient = 1;
	return (color);
}
