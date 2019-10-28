/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:23:13 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/28 14:23:14 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	iso_convert_dot(int x, int y, t_pos dot, t_fdf *s)
{
	t_posi	*dst;

	if (!s)
		free_exit(s, "iso_convert - empty pointer found");
	if (!(dst = &((s->cpy)[y][x])))
		free_exit(s, "iso_convert - empty pointer returned");
	s->scale = (s->scale < 0.05) ? 0.05 : s->scale;
	if (s->projection == TRUE_ISO)
	{
		dst->y = (int)(sin(0.523599) * s->scale * (dot.x + dot.y) - \
				dot.z * s->scale);
		dst->x = (int)(cos(0.523599) * s->scale * (dot.x - dot.y));
	}
	if (s->projection == ISO)
	{
		dst->y = (int)(sin(0.46373398) * s->scale * (dot.x + dot.y) - \
				dot.z * s->scale);
		dst->x = (int)(cos(0.46373398) * s->scale * (dot.x - dot.y));
	}
}

void		iso_convert_array(t_fdf *s)
{
	int		i;
	int		j;
	t_pos	dot;

	if (!s)
		free_exit(s, "iso_convert_array - empty pointer found");
	i = -1;
	while (++i < s->arr_y_size)
	{
		j = -1;
		while (++j < s->arr_x_size)
		{
			dot = rotation(i, j, s);
			iso_convert_dot(j, i, dot, s);
		}
	}
}

static int	is_can_put_line(t_posi a, t_posi b, t_fdf *s)
{
	if (!s)
		free_exit(s, "is_can_put_line - empty pointer found");
	if ((a.x >= -s->shift_x && a.x <= WIN_SIZE_HOR - s->shift_x && \
			a.y >= -s->shift_y && a.y <= WIN_SIZE_VERT - s->shift_y) || \
			(b.x >= -s->shift_x && b.x <= WIN_SIZE_HOR - s->shift_x && \
			b.y >= -s->shift_y && b.y <= WIN_SIZE_VERT - s->shift_y))
		return (1);
	return (0);
}

void		draw_menu(t_fdf *s)
{
	if (!s)
		free_exit(s, "draw_menu - empty pointer found");
	s->line = ft_itoa(s->scale);
	mlx_string_put(s->mlx, s->win, 140, 30, WHITE, s->line);
	ft_strdel(&(s->line));
	s->line = ft_itoa(s->shift_x);
	mlx_string_put(s->mlx, s->win, 140, 50, WHITE, s->line);
	ft_strdel(&(s->line));
	s->line = ft_itoa(s->shift_y);
	mlx_string_put(s->mlx, s->win, 140, 70, WHITE, s->line);
	ft_strdel(&(s->line));
	s->line = ft_itoa((int)(s->angle.x * 100 / 6.3));
	mlx_string_put(s->mlx, s->win, 140, 90, WHITE, s->line);
	ft_strdel(&(s->line));
	s->line = ft_itoa((int)(s->angle.y * 100 / 6.3));
	mlx_string_put(s->mlx, s->win, 140, 110, WHITE, s->line);
	ft_strdel(&(s->line));
	s->line = ft_itoa((int)(s->angle.z * 100 / 6.3));
	mlx_string_put(s->mlx, s->win, 140, 130, WHITE, s->line);
	ft_strdel(&(s->line));
}

void		redraw(t_fdf *s)
{
	t_posi	**arr;
	int		i;
	int		j;

	if (!s)
		free_exit(s, "redraw - empty pointer found");
	iso_convert_array(s);
	arr = s->cpy;
	i = -1;
	while (++i < s->arr_y_size)
	{
		j = -1;
		while (++j < s->arr_x_size)
		{
			if (j < s->arr_x_size - 1 && \
					is_can_put_line(arr[i][j], arr[i][j + 1], s))
				draw_line(arr[i][j], arr[i][j + 1], s);
			if (i < s->arr_y_size - 1 && \
					is_can_put_line(arr[i][j], arr[i + 1][j], s))
				draw_line(arr[i][j], arr[i + 1][j], s);
		}
	}
}
