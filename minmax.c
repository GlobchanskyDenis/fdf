/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:32:09 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/27 16:32:17 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_minmax_xy(t_pos pos, t_fdf *s)
{
	if (!s)
		free_exit(s, "set_minmax_xy - empty pointer found");
	if (s->init_flag == 0)
	{
		s->min.x = pos.x;
		s->max.x = pos.x;
		s->min.y = pos.y;
		s->max.y = pos.y;
	}
	else
	{
		if (s->min.x > pos.x)
			s->min.x = pos.x;
		if (s->min.y > pos.y)
			s->min.y = pos.y;
		if (s->max.x < pos.x)
			s->max.x = pos.x;
		if (s->max.y < pos.y)
			s->max.y = pos.y;
	}
}

void	set_minmax_z(double z, t_fdf *s)
{
	if (!s)
		free_exit(s, "set_minmax_z - empty pointer found");
	if (s->init_flag)
	{
		if (s->max.z < z)
			s->max.z = z;
		if (s->min.z > z)
			s->min.z = z;
	}
	else
	{
		s->max.z = z;
		s->min.z = z;
		s->init_flag = 1;
	}
}
