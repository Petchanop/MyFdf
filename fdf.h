/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:38:27 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/27 22:24:18 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "include/ft_printf/srcs/ft_printf.h"
# include "include/getnextline/get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096 
# endif

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}				t_data;

typedef struct s_point {
	float	x;
	float	y;
}	t_point;

typedef struct s_mapdata {
	int		value;
	int		color;
	t_point	point;
}	t_mapdata;

void	build_image(t_data *img, int width, int length);
void	write_line(t_data img, t_mapdata **data);
void	ft_clear_allocate_data(char	**line_split);
void	ft_free_split(char **split);
void	get_data(char *argv, t_data *img);
int		get_height(char *line);
int		get_width(char *line);
int		ft_findhexvalue(char code);
unsigned int	ft_hextoi(char *code);
t_mapdata	**ft_create_data(t_data *img, char *line);


#endif