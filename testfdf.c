/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:06:55 by npiya-is          #+#    #+#             */
/*   Updated: 2022/09/04 01:46:54 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*ft_lstnew(void *content);

void	ft_lstadd_back(t_list **lst, t_list *new);

int		key_hook(int keycode, t_vars *vars);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	print_data(t_vars vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars.img.height)
	{
		j = 0;
		while (j < vars.img.width)
		{
			if (vars.data[i][j].value)
			{	
				printf("i,j : %d,%d\n", i, j);
				printf("%d", vars.data[i][j].value);
				printf(",%d", vars.data[i][j].color);
			}
			if (vars.data[i][j].value < 10)
				printf("  ");
			if (vars.data[i][j].value >= 10 && vars.data[i][j].value <= 999)
				printf(" ");
			j++;
		}
		printf("\n");
		i++;
	}
}

void	init_t_data(t_vars *vars)
{
	vars->img.img = mlx_new_image(vars->mlx, 1920, 1080);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	if (!vars->img.zoom)
		vars->img.zoom = 1;
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	int			fd;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "npiya-is");
	if (argc == 2)
		get_data(argv[1], &vars.img);
	fd = open(argv[1], O_RDONLY);
	vars.data = ft_create_data(&vars.img, fd);
	close(fd);
	init_t_data(&vars);
	vars.zoom = find_proportion(vars.img);
	vars.center = find_center(vars, vars.data);
	write_line(vars);
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_mouse_hook(vars.mlx_win, mouse_hook, &vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);
}
