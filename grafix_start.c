#include "fdf.h"

static void	get_scale(t_fdf *s)
{
	t_pos	size;

	if (!s)
		free_exit(s, "get_map_size_scale - null pointer found");
	size.x = ft_absd(s->max.x - s->min.x);
	size.y = ft_absd(s->max.y - s->min.y);
	if (size.x > size.y)
		s->scale = (double)WIN_SIZE_HOR / 2 / size.x;
	else
		s->scale = (double)WIN_SIZE_VERT / 2 / size.y;
}

static void	set_point_color(t_fdf *s, t_posi *dst, t_pos *src)
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
	//dst->z = src->z;
}

static void	make_cpy_arr(t_fdf *s)
{
	int		i;
	int		j;

	if (!s)
		free_exit(s, "make_cpy_arr - empty pointer found");
	if (!(s->cpy = (t_posi **)malloc(sizeof(t_posi *) * (s->arr_y_size + 1))))
		free_exit(s, "start_calc - malloc error");
	ft_bzero(s->cpy, sizeof(t_posi *) * (s->arr_y_size + 1));
	i = -1;
	while(++i < s->arr_y_size)
	{
		if (!(s->cpy[i] = (t_posi *)malloc(sizeof(t_posi) * s->arr_x_size)))
			free_exit(s, "start_calc - malloc error");
		ft_bzero(s->cpy[i], sizeof(t_posi) * s->arr_x_size);
		j = -1;
		while (++j < s->arr_x_size)
		set_point_color(s, &(s->cpy[i][j]), &(s->pos[i][j]));
	}
	s->cpy[i] = NULL;
}

void		start_calc(t_fdf *s)
{
	if (!s)
		free_exit(s, "start_calc - empty pointer found");
	s->z_scale = 0.3;
	//s->angle = 0.523599;
	s->is_need_to_redraw = 1;
	s->shift_x = WIN_SIZE_HOR / 2;
	s->shift_y = WIN_SIZE_VERT / 2;
	make_cpy_arr(s);
	//iso_convert_array(s);
	get_scale(s);
}