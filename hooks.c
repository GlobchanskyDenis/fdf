/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:22:39 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/28 14:22:41 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	escape_function(t_fdf *s)
{
	if (!s)
		free_exit(s, "escape_function - null pointer found");
	if (s->win)
	{
		mlx_destroy_window(s->mlx, s->win);
		s->win = NULL;
	}
	free_exit(s, NULL);
}

int			key_hook(int key, t_fdf *s)
{
	if (!s)
		free_exit(s, "key_hook - empty pointer was found");
	if (key == ESCAPE)
		escape_function(s);
	if (key == KEY_UP && (s->is_need_to_redraw = 1))
		s->shift_y -= 15;
	if (key == KEY_DOWN && (s->is_need_to_redraw = 1))
		s->shift_y += 15;
	if (key == KEY_LEFT && (s->is_need_to_redraw = 1))
		s->shift_x -= 15;
	if (key == KEY_RIGHT && (s->is_need_to_redraw = 1))
		s->shift_x += 15;
	if (key == KEY_PLUS && (s->is_need_to_redraw = 1))
		z_increase(s->pos, s);
	if (key == KEY_MINUS && (s->is_need_to_redraw = 1))
		z_decrease(s->pos, s);
	if (key == KEY_X && (s->is_need_to_redraw = 1))
		s->angle.x += 0.1;
	if (key == KEY_Y && (s->is_need_to_redraw = 1))
		s->angle.y += 0.1;
	if (key == KEY_Z && (s->is_need_to_redraw = 1))
		s->angle.z += 0.1;
	if (key == KEY_P && (s->is_need_to_redraw = 1))
		s->projection ^= (1 << 0);
	return (0);
}

int			mouse_hook(int param, int x, int y, t_fdf *s)
{
	if (!s || (!param && !x && !y))
		free_exit(s, "mouse_hook - empty pointer was found");
	if (param == SCROLL_UP && (s->is_need_to_redraw = 1))
		s->scale = s->scale * 1.05;
	if (param == SCROLL_DOWN && (s->is_need_to_redraw = 1))
		s->scale = s->scale / 1.05;
	return (0);
}

static void	draw_menu_list(t_fdf *s)
{
	if (!s)
		free_exit(s, "mouse_hook - empty pointer was found");
	mlx_string_put(s->mlx, s->win, 30, 30, WHITE, "scale    = ");
	mlx_string_put(s->mlx, s->win, 30, 50, WHITE, "camera x = ");
	mlx_string_put(s->mlx, s->win, 30, 70, WHITE, "camera y = ");
	mlx_string_put(s->mlx, s->win, 30, 90, WHITE, "angle x  = ");
	mlx_string_put(s->mlx, s->win, 30, 110, WHITE, "angle y  = ");
	mlx_string_put(s->mlx, s->win, 30, 130, WHITE, "angle z  = ");
	mlx_string_put(s->mlx, s->win, 30, 150, WHITE, "BUTTONS:");
	mlx_string_put(s->mlx, s->win, 30, 170, WHITE, "+ - X Y Z P scroll");
	if (s->projection == TRUE_ISO)
		mlx_string_put(s->mlx, s->win, 30, 190, WHITE, "preojection true iso");
	if (s->projection == ISO)
		mlx_string_put(s->mlx, s->win, 30, 190, WHITE, "preojection iso");
}

int			loop_hook(t_fdf *s)
{
	if (!s)
		free_exit(s, "loop_hook - empty pointer was found");
	if (s->is_need_to_redraw == 1)
	{
		mlx_clear_window(s->mlx, s->win);
		redraw(s);
		draw_menu_list(s);
		draw_menu(s);
		s->is_need_to_redraw = 0;
	}
	return (0);
}
