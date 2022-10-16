/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_checkpoint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:15:37 by npiya-is          #+#    #+#             */
/*   Updated: 2022/10/16 00:39:23 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	valid_point(t_point point)
{
	if (point.x < 1920 && point.y < 1080)
	{	
		if (point.x > 0 && point.y > 0)
			return (1);
	}
	return (0);
}

int	check_stepx(t_point begin, t_point end, t_point step)
{
	if (fabs(step.x) >= fabs(step.y))
	{
		if (step.x > 0)
		{
			if (begin.x < end.x)
				return (1);
		}
		else if (step.x < 0)
		{
			if (begin.x > end.x)
				return (2);
		}
	}
	return (0);
}

int	check_stepy(t_point begin, t_point end, t_point step)
{
	if (fabs(step.x) < fabs(step.y))
	{	
		if (step.y > 0)
		{
			if (begin.y < end.y)
				return (3);
		}
		else if (step.y < 0)
		{
			if (begin.y > end.y)
				return (4);
		}
	}
	return (0);
}

int	check_point(t_point begin, t_point end, t_point step)
{
	if (valid_point(begin))
	{
		if (check_stepx(begin, end, step))
			return (check_stepx(begin, end, step));
		else if (check_stepy(begin, end, step))
			return (check_stepy(begin, end, step));
	}
	return (0);
}
