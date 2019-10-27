#include "fdf.h"

static void	escape_function(t_fdf *s)
{
	//mlx_destroy_image(s->mlx, s->room_img);
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
		s->z_scale += 0.003;
	if (key == KEY_MINUS && (s->is_need_to_redraw = 1))
		s->z_scale -= 0.003;
	if (key == KEY_X && (s->is_need_to_redraw = 1))
		s->x_ang += 0.1;//(s->x_angle + 0.1 < 3) ? s->x_angle + 0.1 : -1; 
	if (key == KEY_Y && (s->is_need_to_redraw = 1))
		s->y_ang += 0.1;
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

int			loop_hook(t_fdf *s)
{
	if (!s)
		return (-1);
	if (s->is_need_to_redraw == 1)
	{
		mlx_clear_window(s->mlx, s->win);
		redraw(s);
		mlx_string_put(s->mlx, s->win, 30, 30, WHITE, "scale    = ");
		mlx_string_put(s->mlx, s->win, 30, 50, WHITE, "camera x = ");
		mlx_string_put(s->mlx, s->win, 30, 70, WHITE, "camera y = ");
		s->line = ft_itoa(s->scale);
		mlx_string_put(s->mlx, s->win, 140, 30, WHITE, s->line);
		ft_strdel(&(s->line));
		s->line = ft_itoa(s->shift_x);
		mlx_string_put(s->mlx, s->win, 140, 50, WHITE, s->line);
		ft_strdel(&(s->line));
		s->line = ft_itoa(s->shift_y);
		mlx_string_put(s->mlx, s->win, 140, 70, WHITE, s->line);
		ft_strdel(&(s->line));
		s->is_need_to_redraw = 0;
	}
	return (0);
}