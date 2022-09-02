/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keymap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:16:26 by npiya-is          #+#    #+#             */
/*   Updated: 2022/09/02 21:46:19 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_t_data(t_vars *vars);

void	ft_clear_allocate_data(t_vars vars);

int	key_hook(int keycode, t_vars *vars)
{
	//printf("key : %d\n", keycode);
	if (keycode == ON_KEYUP)
		vars->center.y -= 10;
	else if (keycode == ON_KEYDOWN)
		vars->center.y += 10;
	else if (keycode == ON_KEYLEFT)
		vars->center.x -= 10;
	else if (keycode == ON_KEYRIGHT)
		vars->center.x += 10;
	else if (keycode == ON_ESCAPE)
	{
		ft_clear_allocate_data(*vars);
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(0);
	}
	mlx_destroy_image(vars->mlx, vars->img.img);
	init_t_data(vars);
	write_line(*vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;

	if (keycode == ON_SCROLLUP)
	{
		vars->img.zoom += 0.1;
		vars->zoom = find_proportion(vars->img);
	}
	else if (keycode == ON_SCROLLDOWN)
	{
		vars->img.zoom -= 0.1;
		vars->zoom = find_proportion(vars->img);
	}
	mlx_destroy_image(vars->mlx, vars->img.img);
	init_t_data(vars);
	write_line(*vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);
	return (0);
}