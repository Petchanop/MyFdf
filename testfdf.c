/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:06:55 by npiya-is          #+#    #+#             */
/*   Updated: 2022/08/15 15:00:45 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*ft_lstnew(void *content);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	build_image(t_data *img, int *width, int *length)
{
	img->bits_per_pixel = 32;
	img->line_length = *width;
	img->endian = *length;
	img->width = width;
	img->height = length;
	printf("bits : %d\n", img->bits_per_pixel);
	printf("width : %d\n", img->line_length);
	printf("endian : %d\n", img->endian);

}

void	del(void *content)
{
	free(content);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	char	*line;
	char	**line_split;
	t_list	*line_array;
	int	**line_bsplit;
	t_data	img;
	int		fd;
	int		i;
	int		j;
	int		x;
	int		y;
	int 	width;
	int		height;

	fd = 0;
	i = 0;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	line = NULL;
	line_array = NULL;
	line_split = NULL;
	line_bsplit = NULL;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "npiya-is");
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		line = get_next_line(fd);
		line_array = ft_lstnew((void *)line);
		width = get_width(line);
		height = get_height_build_lst(fd, line, &line_array);
	}
	line_bsplit = malloc(height * sizeof(line_bsplit));
	//printf("%lu\n", img.endian * sizeof(line_bsplit));
	i = 0;
	while (line_array->next)
	{
		line_bsplit[i] = malloc(width * sizeof(line_bsplit[i]));
		j = 0;
		line_split = ft_split((char *)line_array->content, ' ');
		while (line_split[j])
		{
			//printf("%s", line_split[j]);
			line_bsplit[i][j] = ft_atoi(line_split[j]);
			//printf("%d", line_bsplit[i][j]);
			j++;
		}
		i++;
		line_array = line_array->next;
	}
	i = 0;
	j = 0;
	ft_lstclear(&line_array, del);
	while (line_split[j])
		free(line_split[j++]);
	free(line_split);
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			printf("%d", line_bsplit[i][j]);
			if (line_bsplit[i][j] < 10)
				printf("  ");	
			if (line_bsplit[i][j] >= 10 && line_bsplit[i][j] <= 999)
				printf(" ");	
			j++;
		}
		printf("\n");
		i++;
	}
	close(fd);
	build_image(&img, &width, &height);
	img.img = mlx_new_image(mlx, 1919, 1079);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	write_pixel(img, line_bsplit);
	//write_line(img, start, end);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0,  352);
	i = 0;
	j = 0;
	free(line);
	mlx_loop(mlx);
}
