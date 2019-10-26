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

static void iso_convert(int x, int y, t_fdf *s)
{
	t_pos	**pos;
	t_pos	**cpy;
	//int		x_;
	//int		y_;
	//float	z_;
	//t_pos	sign;

	if (!s)
		free_exit(s, "iso_convert - empty pointer found");
	pos = s->pos_arr;
	cpy = s->cpy_arr;
	if (!pos || !cpy)
		free_exit(s, "iso_convert - empty array pointer found");
	
	//x_ = s->arr_x_size / 2;
	//y_ = s->arr_y_size / 2;
	//z_ = (s->max_z - s->min_z) / 2 + s->min_z;
	
	//fprint("pos x %d y %d z %d\t\t", pos[y][x].x, pos[y][x].y, (int)(pos[y][x].z));


	s->scale = (s->scale < 0.05) ? 0.05 : s->scale;
	cpy[y][x].y = s->camera_y * 10 + (int)(sin(0.523599) * s->scale * (double)(pos[y][x].x + pos[y][x].y) - pos[y][x].z * s->z_scale * s->scale);
	cpy[y][x].x = s->camera_x * 10 + (int)(cos(0.523599) * s->scale * (double)(pos[y][x].x - pos[y][x].y));
	
	
	
//cpy[y][x].y = s->camera_y * 10 + (int)((-(double)pos[y][x].z * s->z_scale + (((double)(pos[y][x].x + pos[y][x].y))) * sin(0.3)) * s->scale);
	//cpy[y][x].x = s->camera_x * 10 + (int)((((double)(pos[y][x].x - pos[y][x].y)) * cos(0.3)) * s->scale);
	//s->line = ft_itoa(y);
	//mlx_string_put(s->mlx, s->win, cpy[y][x].x, cpy[y][x].y, BLUE, s->line);
	//ft_strdel(&(s->line));
	//s->line = ft_itoa(x);
	//mlx_string_put(s->mlx, s->win, cpy[y][x].x + 8, cpy[y][x].y, BLUE, s->line);
	//ft_strdel(&(s->line));
	//fprint("cpy x %d y %d z %d\n", cpy[y][x].x, cpy[y][x].y, (int)(cpy[y][x].z));
	
	//if (pos[y][x].z < z_)
	//	cpy[y][x].y = s->camera_y * 10 + (int)(z_ - pos[y][x].z + (float)(pos[y][x].x + pos[y][x].y) * sin(s->angle)) * s->scale;
	//else
	//	cpy[y][x].y = s->camera_y * 10 + (int)(-z_ + pos[y][x].z + (float)(pos[y][x].x + pos[y][x].y) * sin(s->angle)) * s->scale;
	//if (x < x_)
	//	cpy[y][x].x = s->camera_x * 10 - (x_ - pos[y][x].x) * s->scale;
	//else
	//	cpy[y][x].x = s->camera_x * 10 + (pos[y][x].x - x_) * s->scale;
	//if (y < y_)
	//	cpy[y][x].y = s->camera_y * 10 - (y_ - pos[y][x].y) * s->scale;
	//else
	//	cpy[y][x].y = s->camera_y * 10 + (pos[y][x].y - y_) * s->scale;
}


void		iso_convert_array(t_fdf *s)
{
	int		i;
	int		j;

	if (!s)
		free_exit(s, "iso_convert_array - empty pointer found");
	i = -1;
	while (++i < s->arr_y_size)
	{
		j = -1;
		while (++j < s->arr_x_size)
		{
			iso_convert(j, i, s);
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
			
			//fprint("x %d y %d z %d \t\tcolor %d \t=> r %d g %d b %d\n", j, i, (int)(arr[i][j].z), arr[i][j].color,
			//	get_red(arr[i][j].z, s), get_green(arr[i][j].z, s), get_blue(arr[i][j].z, s));
			
			if (j != s->arr_x_size - 1 && ((arr[i][j].x >= 0 && arr[i][j].x <= WIN_SIZE_HOR && arr[i][j].y >= 0 && arr[i][j].y <= WIN_SIZE_VERT) || (arr[i][j + 1].x >= 0 && arr[i][j + 1].x <= WIN_SIZE_HOR && arr[i][j + 1].y >= 0 && arr[i][j + 1].y <= WIN_SIZE_VERT)))
			{
				draw_line(arr[i][j], arr[i][j + 1], s);
				//s->line = ft_itoa(x);
				//if (arr[i][j].x < arr[i][j + 1].x)
				//	mlx_string_put(s->mlx, s->win, arr[i][j].x + 16, arr[i][j].y - 4, BLUE, "+");
				//else
				//	mlx_string_put(s->mlx, s->win, arr[i][j].x + 16, arr[i][j].y - 4, BLUE, "-");
				//if (arr[i][j].y < arr[i][j + 1].y)
				//	mlx_string_put(s->mlx, s->win, arr[i][j].x - 8, arr[i][j].y - 4, BLUE, "+");
				//else
				//	mlx_string_put(s->mlx, s->win, arr[i][j].x - 8, arr[i][j].y - 4, BLUE, "-");
				//ft_strdel(&(s->line));
			}
			if (i != s->arr_y_size - 1 && ((arr[i][j].x >= 0 && arr[i][j].x <= WIN_SIZE_HOR && arr[i][j].y >= 0 && arr[i][j].y <= WIN_SIZE_VERT) || (arr[i + 1][j].x >= 0 && arr[i + 1][j].x <= WIN_SIZE_HOR && arr[i + 1][j].y >= 0 && arr[i + 1][j].y <= WIN_SIZE_VERT)))
			{
				draw_line(arr[i][j], arr[i + 1][j], s);
				//if (arr[i][j].x < arr[i + 1][j].x)
				//	mlx_string_put(s->mlx, s->win, arr[i][j].x + 16, arr[i][j].y + 4, BLUE, "+");
				//else
				//	mlx_string_put(s->mlx, s->win, arr[i][j].x + 16, arr[i][j].y + 4, BLUE, "-");
				//if (arr[i][j].y < arr[i + 1][j].y)
				//	mlx_string_put(s->mlx, s->win, arr[i][j].x - 8, arr[i][j].y + 4, BLUE, "+");
				//else
				//	mlx_string_put(s->mlx, s->win, arr[i][j].x - 8, arr[i][j].y + 4, BLUE, "-");
			}
			//if (arr[i][j].x >= 0 && arr[i][j].x <= WIN_SIZE_HOR && arr[i][j].y >= 0 && arr[i][j].y <= WIN_SIZE_VERT)
			//{
				//mlx_pixel_put(s->mlx, s->win, arr[i][j].x + 1, arr[i][j].y + 1, arr[i][j].color);
				//mlx_pixel_put(s->mlx, s->win, arr[i][j].x + 1, arr[i][j].y, arr[i][j].color);
				//mlx_pixel_put(s->mlx, s->win, arr[i][j].x, arr[i][j].y + 1, arr[i][j].color);
			//	mlx_pixel_put(s->mlx, s->win, arr[i][j].x, arr[i][j].y, arr[i][j].color);
			//}
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