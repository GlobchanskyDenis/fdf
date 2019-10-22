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
		s->camera_y++;
	if (key == KEY_DOWN && (s->is_need_to_redraw = 1))
		s->camera_y--;
	if (key == KEY_LEFT && (s->is_need_to_redraw = 1))
		s->camera_x--;
	if (key == KEY_RIGHT && (s->is_need_to_redraw = 1))
		s->camera_x++;
	return (0);
}

int			mouse_hook(int param, int x, int y, t_fdf *s)
{
	if (!s || (!param && !x && !y))
		free_exit(s, "mouse_hook - empty pointer was found");
	if (param == SCROLL_UP && (s->is_need_to_redraw = 1))
		s->temp_val++;
	if (param == SCROLL_DOWN && (s->is_need_to_redraw = 1))
		s->temp_val--;
	return (0);
}

int			loop_hook(t_fdf *s)
{
	if (!s)
		return (-1);
	if (s->is_need_to_redraw == 1)
	{
		mlx_clear_window(s->mlx, s->win);
		mlx_string_put(s->mlx, s->win, 30, 30, BLUE, "temp val = ");
		mlx_string_put(s->mlx, s->win, 30, 50, BLUE, "camera x = ");
		mlx_string_put(s->mlx, s->win, 30, 70, BLUE, "camera y = ");
		s->line = ft_itoa(s->temp_val);
		mlx_string_put(s->mlx, s->win, 140, 30, BLUE, s->line);
		ft_strdel(&(s->line));
		s->line = ft_itoa(s->camera_x);
		mlx_string_put(s->mlx, s->win, 140, 50, BLUE, s->line);
		ft_strdel(&(s->line));
		s->line = ft_itoa(s->camera_y);
		mlx_string_put(s->mlx, s->win, 140, 70, BLUE, s->line);
		ft_strdel(&(s->line));
		s->is_need_to_redraw = 0;
	}
	return (0);
}