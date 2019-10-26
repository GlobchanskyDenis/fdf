#include "fdf.h"
/*
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
	//x_ = (x_ % 2) ? (x_ - 1) : x_;
	y_ = s->arr_y_size / 2;
	//y_ = (y_ % 2) ? (y_ - 1) : y_;
	s->scale = (s->scale < 0) ? 0 : s->scale; 
	if (x < x_)
		cpy[y][x].x = s->camera_x * 10 - (x_ - pos[y][x].x) * s->scale;
	else
		cpy[y][x].x = s->camera_x * 10 + (pos[y][x].x - x_) * s->scale;
	if (y < y_)
		cpy[y][x].y = s->camera_y * 10 - (y_ - pos[y][x].y) * s->scale;
	else
		cpy[y][x].y = s->camera_y * 10 + (pos[y][x].y - y_) * s->scale;
}
*/

static void	set_minmax_xy(t_pos pos, int *is_minmax_inited, t_fdf *s)
{
	if (!s || !is_minmax_inited)
		free_exit(s, "set_minmax_xy - empty pointer found");
	if (*is_minmax_inited == 0)
	{
		s->min.x = pos.x;
		s->max.x = pos.x;
		s->min.y = pos.y;
		s->max.y = pos.y;
		*is_minmax_inited = 1;
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

void		set_minmax_z(t_fdf *s, float z)
{
	if (!s)
		free_exit(s, "set_minmax_z - empty pointer found");
	if (s->init_started)
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
		s->init_started = 1;
	}
}

static void iso_convert(int x, int y, int *is_minmax_inited, t_fdf *s)
{
	t_pos	**pos;
	t_pos	**cpy;

	if (!s)
		free_exit(s, "iso_convert - empty pointer found");
	pos = s->pos_arr;
	cpy = s->cpy_arr;
	if (!pos || !cpy)
		free_exit(s, "iso_convert - empty array pointer found");
	s->scale = (s->scale < 0.05) ? 0.05 : s->scale;
	cpy[y][x].y = s->camera_y + (int)(sin(0.523599) * s->scale * (double)(pos[y][x].x + pos[y][x].y) - pos[y][x].z * s->z_scale * s->scale);
	cpy[y][x].x = s->camera_x + (int)(cos(0.523599) * s->scale * (double)(pos[y][x].x - pos[y][x].y));
	set_minmax_xy(cpy[y][x], is_minmax_inited, s);
}

void		iso_convert_array(t_fdf *s)
{
	int		i;
	int		j;
	int		is_minmax_inited;

	if (!s)
		free_exit(s, "iso_convert_array - empty pointer found");
	i = -1;
	is_minmax_inited = 0;
	while (++i < s->arr_y_size)
	{
		j = -1;
		while (++j < s->arr_x_size)
		{
			
			iso_convert(j, i, &is_minmax_inited, s);
			x_rotation(i, j, s);
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
	iso_convert_array(s);
	arr = s->cpy_arr;
	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (++j < s->arr_x_size)
		{
			if (j != s->arr_x_size - 1 && ((arr[i][j].x >= 0 && arr[i][j].x <= WIN_SIZE_HOR && arr[i][j].y >= 0 && arr[i][j].y <= WIN_SIZE_VERT) || (arr[i][j + 1].x >= 0 && arr[i][j + 1].x <= WIN_SIZE_HOR && arr[i][j + 1].y >= 0 && arr[i][j + 1].y <= WIN_SIZE_VERT)))
				draw_line(arr[i][j], arr[i][j + 1], s);
			if (i != s->arr_y_size - 1 && ((arr[i][j].x >= 0 && arr[i][j].x <= WIN_SIZE_HOR && arr[i][j].y >= 0 && arr[i][j].y <= WIN_SIZE_VERT) || (arr[i + 1][j].x >= 0 && arr[i + 1][j].x <= WIN_SIZE_HOR && arr[i + 1][j].y >= 0 && arr[i + 1][j].y <= WIN_SIZE_VERT)))
				draw_line(arr[i][j], arr[i + 1][j], s);
		}
	}
}