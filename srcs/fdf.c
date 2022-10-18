/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:24:04 by npiya-is          #+#    #+#             */
/*   Updated: 2022/10/18 21:19:22 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int	close_fdf(t_vars *vars)
{
	ft_clear_allocate_data(*vars);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
	return (0);
}

void	check_fd(int fd)
{
	if (fd < 0)
	{
		write(2, "File not found\n", 15);
		exit(1);
	}
}

void	print_data(t_vars vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars.img.depth)
	{
		j = 0;
		while (j < vars.img.width)
		{
			if (vars.data[i][j].node.y)
			{	
				ft_printf("x : %.2f", vars.data[i][j].node.x);
				ft_printf("y : %.2f", vars.data[i][j].node.z);
				ft_printf("%.2f", vars.data[i][j].node.y);
			}
			if (vars.data[i][j].node.y < 10)
				ft_printf("  ");
			if (vars.data[i][j].node.y >= 10 && vars.data[i][j].node.y <= 999)
				ft_printf(" ");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	init_t_data(t_vars *vars)
{
	vars->img.img = mlx_new_image(vars->mlx, 1920, 1080);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	if (!vars->angle)
	{
		vars->angle = -0.1326;
		vars->angle1 = -1.2326;
		vars->angle2 = 0.5326;
	}
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	int			fd;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "npiya-is");
	if (argc == 2)
		get_data(argv[1], &vars.img);
	else
	{
		ft_printf("Usage : ./fdf <filename> [ case_size z_size ]\n");
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	check_fd(fd);
	vars.data = ft_create_data(&vars.img, fd);
	close(fd);
	init_t_data(&vars);
	vars.zoom = find_proportion(vars.img);
	vars.center = find_center(vars);
	write_line(vars);
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_mouse_hook(vars.mlx_win, mouse_hook, &vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	mlx_hook(vars.mlx_win, ON_DESTROY, 1L << 0, close_fdf, &vars);
	mlx_loop(vars.mlx);
}
