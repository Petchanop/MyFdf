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

int	get_width(char *line)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			width++;
		i++;
	}
	return (width);
}

int	get_height_build_lst(int fd, char *line, t_list **line_array)
{
	int	x;

	x = 0;
	while (line)
	{
		line = get_next_line(fd);
		ft_lstadd_back(line_array, ft_lstnew((void *)line));
		x++;
	}
	return (x);
}

float	x_transformation(t_point dest, t_point angle)
{
	float	new_point;

	new_point = (dest.x - dest.y) * (angle.x / 2);
	// printf("x : %f\n", new_point);
	return (new_point);
}

float	y_transformation(t_point dest, t_point angle)
{
	float	new_point;

	new_point = (dest.x + dest.y) * (angle.y / 2);
	// printf("y : %f\n", new_point);
	return (new_point);
}

t_point	point_transformation(t_point dest, t_point angle)
{
	t_point	new_point;

	new_point.x = (dest.x - dest.y) * (angle.x / 2);
	new_point.y = (dest.x + dest.y) * (angle.y / 2);
	return (new_point);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	write_line(t_data img, t_point start, t_point end)
{
	int	proportion;
	int	i;

	i = 0;
	printf("x : %f\n", end.x);
	printf("y : %f\n", end.y);
	proportion = end.x / end.y;
	while (start.x < end.x)
	{
		my_mlx_pixel_put(&img, 960 + start.x, start.y, 0X0000FF);
		start.x++;
		i++;
		if (i == proportion)
		{
			start.y += 1;
			i = 0;
		}
	}
}

void	write_pixel(t_data img, int **array)
{
	t_point	start;
	t_point	end;
	int i;
	
	i = 0;
	start.x = 0;
	start.y = 0;
	end.x = img.bits_per_pixel * (*img.width);
	end.y = img.bits_per_pixel * (*img.height);

	printf("x : %f\n", end.x);
	printf("y : %f\n", end.y);
	if (array)
		printf("test\n");
	//write_horizontal_line(img, start);
	write_vertical_line(img, start);
}

void	write_horizontal_line(t_data img, t_point start)
{
	t_point x;
	t_point	dx;
	t_point	end;
	int	i;

	x = start;
	end = start;
	dx.x = 64;
	dx.y = 32;
		i = 0;
		while (i < *img.width)
		{
			start.x++;	
			end = point_transformation(start, dx);
			// my_mlx_pixel_put(&img, 960 + x_transformation(x, dx), y_transformation(x, dx), 0X0000FF);
			write_line(img, x, end);
			x = end;
		i++;
		//printf("i : %d\n", i);
		}
	//printf("x, y: %f %f", x.x, x.y);
}

void	write_vertical_line(t_data img, t_point start)
{
	t_point	y;
	t_point	end;
	t_point	dy;
	int	i;

	i = *img.height;
	y = start.y * i;
	end = start;
	dy.x = 64;
	dy.y = 32;
	while (i > 0)
	{
		// while (y.y < end.y && y.x > (end.x * -1))
		// {
			start.y++;	
			end = point_transformation(start, dy);
			// my_mlx_pixel_put(&img, 960 + x_transformation(y , dy), y_transformation(y, dy), 0X0000FF);
			write_line(img, y, end);
			y = end;
			//printf("x, y: %f %f\n", y.x, y.y);
		// }
		// start.y += img.bits_per_pixel; 
		// end.y += img.bits_per_pixel;
		// y = start;
	 	i++;
	}
}

