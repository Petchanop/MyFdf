/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:38:27 by npiya-is          #+#    #+#             */
/*   Updated: 2022/09/02 16:49:15 by npiya-is         ###   ########.fr       */
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

# ifndef Pi
#  define Pi 0.3141592
# endif

# define ON_KEYDOWN 125
# define ON_KEYUP 126
# define ON_KEYLEFT 123 
# define ON_KEYRIGHT 124 
# define ON_EXPOSE 12
# define ON_DESTROY 17
# define ON_ESCAPE 53

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
typedef struct s_vars {
	void		*mlx;
	void		*mlx_win;
	t_mapdata	**data;
	t_data		img;
	t_point		center;
}				t_vars;

void	build_image(t_data *img, int width, int length);
void	write_line(t_vars vars);
void	write_horizontal_line(t_point start, t_point end, t_mapdata data, t_data img);
void	write_vertical_line(t_point start, t_point end, t_mapdata data, t_data img);
void	ft_clear_allocate_data(char	**line_split);
void	ft_free_split(char **split);
void	get_data(char *argv, t_data *img);
int		get_height(char *line);
int		get_width(char *line);
int		ft_findhexvalue(char code);
//int		key_hook(int keycode, t_vars *vars);
unsigned int	ft_hextoi(char *code);
t_point	find_center(t_data img, t_mapdata **data);
t_point	point_transformation(t_mapdata dst, t_point center, t_data img);
t_mapdata	**ft_create_data(t_data *img, int fd);

#endif