/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:38:27 by npiya-is          #+#    #+#             */
/*   Updated: 2022/09/15 01:00:31 by npiya-is         ###   ########.fr       */
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
#  define Pi  3.14159
# endif

# define ON_KEYDOWN 125
# define ON_KEYUP 126
# define ON_KEYLEFT 123 
# define ON_KEYRIGHT 124 
# define ON_EXPOSE 12
# define ON_DESTROY 17
# define ON_ESCAPE 53
# define ON_SCROLLUP 5
# define ON_SCROLLDOWN 4
# define ON_LEFTCLICK 1
# define ON_RIGHTCLICK 2
# define ON_Y 16 
# define ON_Z 6 
# define ON_X 7 

typedef struct s_data {
	void	*img;
	char	*addr;
	float	zoom;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		depth;
	int		width;
}				t_data;

typedef struct s_point {
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_node {
	float	x;
	float	y;
	float	z;
}	t_node;

typedef struct s_map {
	int		color;
	t_point	node;
	t_point	next;
}	t_map;
typedef struct s_vars {
	void		*mlx;
	void		*mlx_win;
	t_map		**data;
	t_data		img;
	t_point		center;
	t_point		zoom;
	float		angle;
	int			mode;
}				t_vars;

void			assign_point(t_vars *vars);
void			build_image(t_data *img, int width, int length);
void			write_line(t_vars vars);
void			write_horizontal(t_point start, t_point end, t_map data, t_data img);
void			write_vertical(t_point start, t_point end, t_map data, t_data img);
void			ft_clear_allocate_data(t_vars vars);
void			ft_free_split(char **split);
void			get_data(char *argv, t_data *img);
int				get_height(char *line);
int				get_width(char *line);
int				ft_findhexvalue(char code);
int				key_hook(int keycode, t_vars *vars);
int				mouse_hook(int keycode, int x, int y, t_vars *vars);
t_point			plot_point(t_map *dst, t_vars vars);
t_point			adjust_point(t_point pnt, t_vars vars);
t_point			find_center(t_vars vars, t_map **data);
t_point			find_proportion(t_data img);
t_point			y_point_transformation(t_map *dst, t_vars vars);
t_point			x_point_transformation(t_map *dst, t_vars vars);
t_point			z_point_transformation(t_map *dst, t_vars vars);
t_map			**ft_create_data(t_data *img, int fd);
unsigned int	ft_hextoi(char *code);

#endif

/*Rotation around the Y axis

TEMPX = X * COS R2 - Z * SIN R2

TEMPZ = X * SIN R2 + Z * COS R2

 

Rotation around the X axis

Zf = TEMPZ * COS R1 - Y * SIN R1

TEMPY = TEMPZ * SIN R1 + Y * COS R1

 

Rotation around the Z axis

Xf = TEMPX * COS R3 + TEMPY * SIN R3

Yf = TEMPY * COS R3 - TEMPX * SIN R3*/