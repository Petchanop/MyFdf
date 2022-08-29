/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:06:55 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/29 23:45:57 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*ft_lstnew(void *content);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*mlx_win;
	t_mapdata	**line_bsplit;
	t_data		img;
	// int	i = 0;
	// int	j = 0;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "npiya-is");
	if (argc == 2)
		get_data(argv[1], &img);
	line_bsplit = ft_create_data(&img, argv[1]);
	// while (i < img.endian)
	// {
	//  	j = 0;
	// 	while (j < img.line_length)
	// 	{
			// printf("%d", line_bsplit[i][j].value);
			// printf(",%d", line_bsplit[i][j].color);
			//printf(" x,y %.2f,%.2f\n", line_bsplit[i][j].point.x, line_bsplit[i][j].point.y );
			// if (line_bsplit[i][j].value < 10)
			// 	printf("  ");	
			// if (line_bsplit[i][j].value >= 10 && line_bsplit[i][j].value <= 999)
			// 	printf(" ");	
	// 		j++;
	// 	}
	// 	i++;
	// }
	printf("\n");
	img.img = mlx_new_image(mlx, 1919, 1079);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	write_line(img, line_bsplit);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
