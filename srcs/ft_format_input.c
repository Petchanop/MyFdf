/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:49:00 by npiya-is          #+#    #+#             */
/*   Updated: 2022/10/17 00:13:40 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	ft_time(unsigned int base, int times)
{
	int				i;
	unsigned int	time;

	i = 1;
	time = base;
	if (times == 0)
		return (1);
	while (i < times)
	{
		time *= base;
		i++;
	}
	return (time);
}

int	ft_findhexvalue(char code)
{
	int		i;
	char	*hex;
	char	*hex_low;

	i = 0;
	hex = "0123456789ABCDEF";
	hex_low = "0123456789abcdef";
	while (hex[i])
	{
		if (hex[i] == code || hex_low[i] == code)
			return (i);
		i++;
	}
	return (i);
}

unsigned int	ft_hextoi(char *code)
{
	unsigned int	num;
	unsigned int	val;
	int				i;
	int				j;

	num = 0;
	i = 2;
	j = ft_strlen(code) - 3;
	while (code[i])
	{
		if (code[i] == '\n')
			break ;
		val = ft_findhexvalue(code[i]);
		num += val * ft_time(16, j);
		i++;
		j--;
	}
	return (num);
}

void	build_image(t_data *img, int width, int length)
{
	img->bits_per_pixel = 32;
	img->line_length = width;
	img->endian = length;
	img->width = width;
	img->depth = length;
	img->zoom = 1.0;
}

void	ft_clear_allocate_data(t_vars vars)
{
	int	i;

	i = 0;
	while (i < vars.img.depth)
		free(vars.data[i++]);
}
