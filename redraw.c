#include "fdf.h"

void		redraw(t_fdf *s)
{
	t_pos	**arr;
	int		i;
	int		j;

	if (!s)
		free_exit(s, "redraw - empty pointer found");
	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (++j < s->arr_x_size)
		{
			mlx_pixel_put(s->mlx, s->win, arr[i][j].x, arr[i][j].y, arr[i][j].color);
		}
	}
}

void		set_minmax_z(t_fdf *s, int z)
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