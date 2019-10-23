#include "fdf.h"

static void	convert_dot(int x, int y, t_fdf *s)
{
	t_pos	**pos;
	t_pos	**cpy;
	int		x_;
	int		y_;

	if (!s)
		free_exit(s, "convert_dot - empty pointer found");
	pos = s->pos_arr;
	cpy = s->cpy_arr;
	if (!pos || !cpy)
		free_exit(s, "convert_dot - empty array pointer found");
	x_ = s->arr_x_size / 2;
	//x_ = (x_ % 2) ? (x_ + 2) : x_;
	y_ = s->arr_y_size / 2;
	//y_ = (y_ % 2) ? (y_ + 2) : y_;
	s->scale = (s->scale < 0) ? 0 : s->scale; 
	if (x < x_)
		cpy[y][x].x = s->camera_x * 10 - (x_ - pos[y][x].x) * s->scale;
	else
		cpy[y][x].x = s->camera_x * 10 + (pos[y][x].x - x_) * s->scale;
	if (y < y_)
		cpy[y][x].y = s->camera_y * 10 - (x_ - pos[y][x].y) * s->scale;
	else
		cpy[y][x].y = s->camera_y * 10 + (pos[y][x].y - y_) * s->scale;
}

static void	convert_dots(t_fdf *s)
{
	int		i;
	int		j;

	if (!s)
		free_exit(s, "convert_dots - empty pointer found");
	i = -1;
	while (++i < s->arr_y_size)
	{
		j = -1;
		while (++j < s->arr_x_size)
		{
			convert_dot(j, i, s);
		}
	}
}

void		redraw(t_fdf *s)
{
	t_pos	**arr;
	int		i;
	int		j;

	if (!s)
		free_exit(s, "redraw - empty pointer found");
	convert_dots(s);
	arr = s->cpy_arr;
	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (++j < s->arr_x_size)
		{
			//fprint("pixel put %d %d %d\n", j, i, arr[i][j].color);
			if (j != s->arr_x_size - 1)
				draw_line(arr[i][j], arr[i][j + 1], 0x111111, s);
			if (i != s->arr_y_size - 1)
				draw_line(arr[i][j], arr[i + 1][j], 0x111111, s);
			mlx_pixel_put(s->mlx, s->win, arr[i][j].x + 1, arr[i][j].y + 1, arr[i][j].color);
			mlx_pixel_put(s->mlx, s->win, arr[i][j].x + 1, arr[i][j].y, arr[i][j].color);
			mlx_pixel_put(s->mlx, s->win, arr[i][j].x, arr[i][j].y + 1, arr[i][j].color);
			mlx_pixel_put(s->mlx, s->win, arr[i][j].x, arr[i][j].y, arr[i][j].color);
		}
	}
}

void		set_minmax_z(t_fdf *s, float z)
{
	if (!s)
		free_exit(s, "set_minmax_z - empty pointer found");
	if (s->init_started)
	{
		if (s->max_z < z)
			s->max_z = z;
		if (s->min_z > z)
			s->min_z = z;
	}
	else
	{
		s->max_z = z;
		s->min_z = z;
		s->init_started = 1;
	}
}