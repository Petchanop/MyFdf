/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:49:37 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/15 15:38:541:12 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	point_transformation(t_point dest, int width, int height)
{
	t_point	new_point;

	new_point.x = (dest.x - dest.y) * (width / 2);
	new_point.y = (dest.x + dest.y) * (height / 2);
	return (new_point);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	write_line(t_data img, t_mapdata **data)
{
	int	i;
	int	j;
	t_point	plot;

	i = 0;
	while (i < img.height)
	{
		j = 0;
		while (j < img.width)
		{
			plot = point_transformation(data[i][j].point, 64, 32);
			printf("plot : %.2f,%.2f\n", plot.x, plot.y);
			my_mlx_pixel_put(&img, 960 + plot.x, plot.y, 0x0000FF);
			j++;
		}
		i++;
	}
}