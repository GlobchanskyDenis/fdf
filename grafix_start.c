#include "fdf.h"

static int	get_point_color(t_fdf *s, int z)
{
	if (!s)
		free_exit(s, "get_point_color - null pointer found");
	if (z <= 0)
		return (BLUE);
	if (z < s->max_z / 3)
		return (GREEN);
	if (z < s->max_z * 2 / 3)
		return (0xFFFF00);
	return (RED);
}

static void	set_point_color(t_fdf *s, t_pos *dst, t_pos *src)
{
	if (!s || !dst || !src)
		free_exit(s, "set_point_color - null pointer found");
	if (s->color_exists)
	{
		if ((*src).color)
			(*dst).color = (*src).color;
		else
			(*dst).color = WHITE;
	}
	else
		(*dst).color = get_point_color(s, (*src).z);
	(*dst).z = (*src).z;
}

static void	make_cpy_arr(t_fdf *s)
{
	int		i;
	int		j;

	if (!s)
		free_exit(s, "make_cpy_arr - empty pointer found");
	if (!(s->cpy_arr = (t_pos **)malloc(sizeof(t_pos *) * (s->arr_y_size + 1))))
		free_exit(s, "start_calc - malloc error");
	ft_bzero(s->cpy_arr, sizeof(t_pos *) * (s->arr_y_size + 1));
	if (s->cpy_arr[s->arr_y_size])
		fprint("bzero error\n");
	i = -1;
	while(++i < s->arr_y_size)
	{
		if (!(s->cpy_arr[i] = (t_pos *)malloc(sizeof(t_pos) * s->arr_x_size)))
			free_exit(s, "start_calc - malloc error");
		ft_bzero(s->cpy_arr[i], sizeof(t_pos) * s->arr_x_size);
		j = -1;
		while (++j < s->arr_x_size)
			set_point_color(s, &(s->cpy_arr[i][j]), &(s->pos_arr[i][j]));
	}
}

void		start_calc(t_fdf *s)
{
	if (!s)
		free_exit(s, "start_calc - empty pointer found");
	s->temp_val = 100;
	s->camera_x = 100;
	s->camera_y = 100;
	s->is_need_to_redraw = 1;
	make_cpy_arr(s);
}