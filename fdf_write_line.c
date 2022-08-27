/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_write_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 23:57:40 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/26 18:29:03 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	point_transformation(t_point dest, t_point angle)
{
	t_point	new_point;

	new_point.x = (dest.x - dest.y) * (angle.x / 2);
	new_point.y = (dest.x + dest.y) * (angle.y / 2);
	return (new_point);
}

void	write_line(t_data img, t_point start, t_point end, t_mapdata *data)
{
	t_point	pre;
	t_point	dy;
	t_point	new_point;
	t_point	pre_ver;
	t_point	new_ver;
	int	i;
	int	color;

	new_point = start;
	new_ver.y = start.x;
	new_ver.x = start.y;
	dy.x = 64;
	dy.y = 32;
	i = 0; 
	color = 255;
	//printf("start   : %f , %f\n", start.x, start.y);
	while (i < end.x && new_point.y < 1080 )//&& i < 1)
	{
		pre = new_point;
		pre_ver = new_ver;
		if (i < end.y && data && data[i].color != 0)
			color = data[i].color;
		else
			color = 255; 
		new_point.x++;
		new_ver.y++;
		// printf("pre   : %f , %f\n", pre.x, pre.y);
		// printf("point : %f , %f\n", new_point.x, new_point.y);
		write_horizontal_line(img, pre, new_point, data[i]);
		write_vertical_line(img, new_ver, pre_ver, data[i]);
		i++;
	}
}

void	write_horizontal_line(t_data img, t_point point, t_point new_point, t_mapdata data)
{
	t_point	start;
	t_point	end;
	int	i;
	int	j;
	int color;
	t_point	dy;

	i = 0;
	dy.x = 64;
	dy.y = 32;
	if (data.color == 0) 
		color = 255;

	while (i < end.y)
	{
		start.x = 0;
		start.y = i;
		j = 0;
		while (j < end.x && new_point.y < 1080 )//&& i < 1)
		{
			pre = new_point;
			if (i < end.y && data && data[i].color != 0)
				color = data[i].color;
			else
				color = 255; 
			new_point.x++;
			start = point_transformation(point, dy);
			end = point_transformation(new_point, dy);
		//printf("x0,y0 : %f %f\n", start.x, start.y);
			while (start.x < end.x && end.x < 1920 && end.y < 1080)
			{
				my_mlx_pixel_put(&img, 960 + start.x, start.y, color);
				start.x++;
				start.y += (dy.y / dy.x);
			}
			j++;
		}
		i++;
	}
	//printf("x1,y1 : %f %f\n", start.x, start.y);
}

void	write_vertical_line(t_data img, t_point point, t_point new_point, t_mapdata data)
{
	t_point	start;
	t_point	end;
	int	i;
	int color;
	t_point	dy;

	i = 0;
	dy.x = 64;
	dy.y = 32;
	if (data.color == 0) 
		color = 255;
	while (i < end.x)
	{
		start_ver.x = i;
		start_ver.y = 0;
		while (j < end.x && new_point.y < 1080 )//&& i < 1)
		{
			pre = new_point;
			if (i < end.y && data && data[i].color != 0)
				color = data[i].color;
			else
				color = 255; 
			new_point.y++;
			start = point_transformation(point, dy);
			end = point_transformation(new_point, dy);
			printf("x0,y0 : %f %f\n", start.x, start.y);
			while (start.x < end.x && end.x < 1920 && end.y < 1080)
			{
				my_mlx_pixel_put(&img, 960 + start.x, start.y, color);
				start.x++;
				start.y -= (dy.y / dy.x);
			}
			j++;
		}
	printf("x1,y1 : %f %f\n", start.x, start.y);
	}
}

void	write_pixel(t_data img, t_mapdata **array)
{
	t_point	start;
	t_point	start_ver;
	t_point	end;
	int i;
	
	i = 0;
	start.x = 0;
	start.y = 0;
	start_ver.x = 0;
	start_ver.y = 0;
	end.x = *img.width;
	end.y = *img.height;
	printf("x : %f %f\n", end.x, img.endian);
	printf("y : %f %f\n", end.y, img.line_length);
	if (array)
		printf("test\n");
	while (i < end.y)
	{
		start.x = 0;
		start.y = i;
		// start_ver.x = i;
		// start_ver.y = 0;
		write_line(img, start, end, array[i]);
		//write_line(img, start_ver, end, array[i]);
		printf("line : %d\n", i + 1);
		i++;
	}
	// i = 0;
	// while (i < end.x)
	// {
	// 	start_ver.x = i;
	// 	start_ver.y = 0;
	// 	write_line(img, start_ver, end, array[i]);
	// 	printf("line : %d\n", i + 1);
	// 	i++;	
	// }
}