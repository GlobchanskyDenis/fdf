#include "fdf.h"

static void iso_convert_dot(int x, int y, t_fdf *s)
{
	t_pos	**pos;
	t_posi	**cpy;

	if (!s)
		free_exit(s, "iso_convert - empty pointer found");
	pos = s->pos;
	cpy = s->cpy;
	if (!pos || !cpy)
		free_exit(s, "iso_convert - empty array pointer found");
	s->scale = (s->scale < 0.05) ? 0.05 : s->scale;
	cpy[y][x].y = (int)(sin(0.523599) * s->scale * (pos[y][x].x + pos[y][x].y) - pos[y][x].z * s->z_scale * s->scale);
	cpy[y][x].x = (int)(cos(0.523599) * s->scale * (pos[y][x].x - pos[y][x].y));
	//set_minmax_xy(cpy[y][x], s);
	//set_minmax_z(pos.z, s);
}

void		iso_convert_array(t_fdf *s)
{
	int		i;
	int		j;

	if (!s)
		free_exit(s, "iso_convert_array - empty pointer found");
	i = -1;
	//s->init_flag = 0;
	while (++i < s->arr_y_size)
	{
		j = -1;
		while (++j < s->arr_x_size)
		{
			x_rotation(i, j, s);
			iso_convert_dot(j, i, s);
		}
	}
}

static int	is_can_put_line(t_posi a, t_posi b, t_fdf *s)
{
	if (!s)
		free_exit(s, "is_can_put_line - empty pointer found");
	if ((a.x >= -(s->shift_x) && a.x <= WIN_SIZE_HOR / 2 && \
			a.y >= -(s->shift_y) && a.y <= WIN_SIZE_VERT / 2) || \
			(b.x >= -(s->shift_x) && b.x <= WIN_SIZE_HOR / 2 && \
			b.y >= -(s->shift_y) && b.y <= WIN_SIZE_VERT / 2))
		return (1);
	return (0);
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
		//fprint("y = %d\t", i);
		j = -1;
		while (++j < s->arr_x_size)
		{
			//fprint(" %d", j);
			//if (j != s->arr_x_size - 1 && ((arr[i][j].x >= -s->shift_x && arr[i][j].x <= WIN_SIZE_HOR - s->shift_x && arr[i][j].y >= -s->shift_y && arr[i][j].y <= WIN_SIZE_VERT - s->shift_y) || (arr[i][j + 1].x >= -s->shift_x && arr[i][j + 1].x <= WIN_SIZE_HOR - s->shift_x && arr[i][j + 1].y >= -s->shift_y && arr[i][j + 1].y <= WIN_SIZE_VERT - s->shift_y)))
			if (j != s->arr_x_size - 1 && is_can_put_line(arr[i][j], arr[i][j + 1], s))	
				draw_line(arr[i][j], arr[i][j + 1], s);
			//if (i != s->arr_y_size - 1 && ((arr[i][j].x >= -s->shift_x && arr[i][j].x <= WIN_SIZE_HOR - s->shift_x && arr[i][j].y >= -s->shift_y && arr[i][j].y <= WIN_SIZE_VERT - s->shift_y) || (arr[i + 1][j].x >= -s->shift_x && arr[i + 1][j].x <= WIN_SIZE_HOR - s->shift_x && arr[i + 1][j].y >= -s->shift_y && arr[i + 1][j].y <= WIN_SIZE_VERT - s->shift_y)))
			if (i != s->arr_y_size - 1 && is_can_put_line(arr[i][j], arr[i + 1][j], s))	
				draw_line(arr[i][j], arr[i + 1][j], s);
		}
		//fprint("\n");
	}
}