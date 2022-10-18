/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keymap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:16:26 by npiya-is          #+#    #+#             */
/*   Updated: 2022/10/18 21:19:29 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	re_project3d(t_vars *vars)
{
	vars->zoom = find_proportion(vars->img);
	mlx_destroy_image(vars->mlx, vars->img.img);
	init_t_data(vars);
	write_line(*vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ON_KEYUP)
		vars->center.y -= 10;
	else if (keycode == ON_KEYDOWN)
		vars->center.y += 10;
	else if (keycode == ON_KEYLEFT)
		vars->center.x -= 10;
	else if (keycode == ON_KEYRIGHT)
		vars->center.x += 10;
	else if (keycode == ON_X)
		vars->mode = 1;
	else if (keycode == ON_Z)
		vars->mode = 2;
	else if (keycode == ON_Y)
		vars->mode = 0;
	else if (keycode == ON_ESCAPE)
	{
		ft_clear_allocate_data(*vars);
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(0);
	}
	re_project3d(vars);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (keycode == ON_SCROLLUP)
		vars->img.zoom += 0.05;
	else if (keycode == ON_SCROLLDOWN)
		vars->img.zoom -= 0.05;
	else if (keycode == ON_RIGHTCLICK && vars->mode == 0)
		vars->angle += 0.05;
	else if (keycode == ON_LEFTCLICK && vars->mode == 0)
		vars->angle -= 0.05;
	else if (keycode == ON_RIGHTCLICK && vars->mode == 1)
		vars->angle1 += 0.05;
	else if (keycode == ON_LEFTCLICK && vars->mode == 1)
		vars->angle1 -= 0.05;
	else if (keycode == ON_RIGHTCLICK && vars->mode == 2)
		vars->angle2 += 0.05;
	else if (keycode == ON_LEFTCLICK && vars->mode == 2)
		vars->angle2 -= 0.05;
	re_project3d(vars);
	return (0);
}
