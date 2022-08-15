/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:38:27 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/15 14:53:17 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include "mlx/mlx.h"
# include "include/ft_printf/srcs/ft_printf.h"
# include "include/getnextline/get_next_line.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		*height;
	int		*width;
}				t_data;

typedef struct s_point {
	float	x;
	float	y;
	float	angle;
}	t_point;

void	write_pixel(t_data img, int **array);
void	write_horizontal_line(t_data img, t_point start);
void	write_vertical_line(t_data img, t_point start);
int		get_height_build_lst(int fd, char *line, t_list **line_array);
int		get_width(char *line);

#endif