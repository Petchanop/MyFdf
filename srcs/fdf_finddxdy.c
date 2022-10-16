/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_finddxdy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:30:41 by npiya-is          #+#    #+#             */
/*   Updated: 2022/10/15 23:36:33 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	find_dxdy(t_point start, t_point end)
{
	t_point		diff;

	diff.x = (end.x - start.x);
	diff.y = (end.y - start.y);
	diff.z = (end.z - start.z);
	return (diff);
}

float	find_stepxy(t_point diff)
{
	if (fabs(diff.x) >= fabs(diff.y))
		return (fabs(diff.x));
	else
		return (fabs(diff.y));
}

float	find_stepxz(t_point diff)
{
	if (fabs(diff.x) >= fabs(diff.z))
		return (fabs(diff.x));
	else
		return (fabs(diff.z));
}
