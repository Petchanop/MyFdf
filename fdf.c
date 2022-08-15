/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:24:04 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/08 23:30:56 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	line = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		line = get_next_line(fd);
		while (line)
		{

		}	
	}

	mlx = mlx_init();
	//create_img_data(&img);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "npiya-is");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}