/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:23:33 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/28 14:23:35 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	z_increase(t_pos **arr, t_fdf *s)
{
	int		i;
	int		j;
	t_pos	*a;
	int		x_size;

	if (!arr || !s)
		free_exit(s, "z_increase - empty pointer found");
	x_size = s->arr_x_size;
	i = -1;
	while (++i < s->arr_y_size)
	{
		a = arr[i];
		j = -1;
		while (++j < x_size)
			a[j].z *= Z_SCALE;
	}
}

void	z_decrease(t_pos **arr, t_fdf *s)
{
	int		i;
	int		j;
	t_pos	*a;
	int		x_size;

	if (!arr || !s)
		free_exit(s, "z_increase - empty pointer found");
	x_size = s->arr_x_size;
	i = -1;
	while (++i < s->arr_y_size)
	{
		a = arr[i];
		j = -1;
		while (++j < x_size)
			a[j].z /= Z_SCALE;
	}
}

int		check_angle(t_fdf *s)
{
	if (!s)
		free_exit(s, "check_angle - null pointer found\n");
	if (s->angle.x > 6.3)
		s->angle.x -= 6.3;
	if (s->angle.y > 6.3)
		s->angle.y -= 6.3;
	if (s->angle.z > 6.3)
		s->angle.z -= 6.3;
	return (1);
}

t_pos	rotation(int i, int j, t_fdf *s)
{
	t_pos	dot;
	t_pos	old;

	if (!s || !(s->pos) || !check_angle(s))
		free_exit(s, "rotation - null pointer found");
	dot = s->pos[i][j];
	if (s->angle.x != 0)
	{
		old = dot;
		dot.y = old.y * cos(s->angle.x) + old.z * sin(s->angle.x);
		dot.z = old.z * cos(s->angle.x) - old.y * sin(s->angle.x);
	}
	if (s->angle.y != 0)
	{
		old = dot;
		dot.x = old.x * cos(s->angle.y) + old.z * sin(s->angle.y);
		dot.z = old.z * cos(s->angle.y) - old.x * sin(s->angle.y);
	}
	if (s->angle.z != 0)
	{
		old = dot;
		dot.y = old.y * cos(s->angle.z) + old.x * sin(s->angle.z);
		dot.x = old.x * cos(s->angle.z) - old.y * sin(s->angle.z);
	}
	return (dot);
}
