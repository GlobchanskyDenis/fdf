#include "fdf.h"

static void		init_delta(t_pos *a, t_pos *b, t_pos *delta, t_fdf *s)
{
	if (!a || !b || !delta || !s)
		free_exit(s, "drow_line - empty pointer was found");
	delta->x = (int)ft_absi(b->x - a->x);
	delta->y = (int)ft_absi(b->y - a->y);
}

static void		logic(t_pos *a, t_pos *delta, t_pos *sign, int *error)
{
	if (!a || !delta || !sign || !error)
		return ;
	if (error[1] > -delta->y)
	{
		error[0] -= delta->y;
		a->x += sign->x;
	}
	if (error[1] < delta->x)
	{
		error[0] += delta->x;
		a->y += sign->y;
	}
}

static float	found_z(t_pos a, t_pos b, t_pos current, t_fdf *s)
{
	float	persent;
	float	z;

	if (!s)
		free_exit(s, "found_z - empty pointer was found");
	if (ft_absi(a.x - b.x) >= ft_absi(a.y - b.y))
		persent = ((float)(current.x - ft_mini(a.x, b.x))) / (float)(ft_absi(a.x - b.x));
	else
		persent = ((float)(current.y - ft_mini(a.y, b.y))) / (float)(ft_absi(a.y - b.y));
	persent = persent * ft_absf(b.z - a.z);
	if (b.z >= a.z)
		z = persent + a.z;
	else
		z = a.z - persent;
	return (z);
}

void			draw_line(t_pos a, t_pos b, t_fdf *s)
{
	t_pos	delta;
	t_pos	sign;
	t_pos	current;
	int		error[2];

	if (!s)
		free_exit(s, "drow_line - empty pointer was found");
	current = a;
	init_delta(&current, &b, &delta, s);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	mlx_pixel_put(s->mlx, s->win, b.x, b.y, get_point_color(b.z, s));
	while (current.x != b.x || current.y != b.y)
	{
		current.z = found_z(a, b, current, s);
		mlx_pixel_put(s->mlx, s->win, current.x, current.y, get_point_color(current.z, s));
		error[1] = error[0] * 2;
		logic(&current, &delta, &sign, error);
	}
}