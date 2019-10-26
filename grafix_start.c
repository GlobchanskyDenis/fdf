#include "fdf.h"

static void	get_map_size_scale(t_fdf *s)
{
	t_pos	size;
	int		max_size;

	if (!s)
		free_exit(s, "get_map_size_scale - null pointer found");
	size.x = ft_absi(s->max.x - s->min.x);
	size.y = ft_absi(s->max.y - s->min.y);
	if (size.x > size.y)
		max_size = size.x;
	else
		max_size = size.y;
	s->scale = (double)WIN_SIZE_VERT * 9 / (double)max_size;
	iso_convert_array(s);
	size.x = ft_absi(s->max.x - s->min.x);
	size.y = ft_absi(s->max.y - s->min.y);
	fprint("xmin %d xmax %d ymin %d ymax %d\n", s->min.x, s->max.x, s->min.y, s->max.y);
	s->camera_x = (WIN_SIZE_HOR - size.x) / 2 - s->min.x;
	s->camera_y = (WIN_SIZE_VERT - size.y)/ 2 - s->min.y;
}

static void	set_point_color(t_fdf *s, t_pos *dst, t_pos *src)
{
	if (!s || !dst || !src)
		free_exit(s, "set_point_color - null pointer found");
	if (s->color_exists)
	{
		if (src->color)
			dst->color = src->color;
		else
			dst->color = WHITE;
	}
	else
		dst->color = get_point_color(src->z, s);
	dst->z = src->z;
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
	s->z_scale = 0.1;
	//s->angle = 0.523599;
	s->is_need_to_redraw = 1;
	s->camera_x = 0;
	s->camera_y = 0;
	s->scale = 10;
	make_cpy_arr(s);
	iso_convert_array(s);
	get_map_size_scale(s);
}