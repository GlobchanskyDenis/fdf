#include "fdf.h"

int _get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

double _percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

int _get_color(t_pos current, t_pos start, t_pos end, t_pos delta)
{
    int     red;
    int     green;
    int     blue;
    double  percentage;

    if (current.color == end.color)
        return (current.color);
    if (delta.x > delta.y)
        percentage = _percent(start.x, end.x, current.x);
    else
        percentage = _percent(start.y, end.y, current.y);
    red = _get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
    green = _get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
    blue = _get_light(start.color & 0xFF, end.color & 0xFF, percentage);
    return ((red << 16) | (green << 8) | blue);
}
/*
static void		init_delta(t_pos *a, t_pos *b, t_pos *delta, t_fdf *s)
{
	if (!a || !b || !delta || !s)
		free_exit(s, "drow_line - empty pointer was found");
	delta->x = (int)ft_absi(b->x - a->x);
	delta->y = (int)ft_absi(b->y - a->y);
}
*/
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
/*
static float	found_z(t_pos a, t_pos b, t_pos current, t_fdf *s, t_pos sign)
{
	float	persent;
	float	z;
	//int		flag;

	if (!s)
		free_exit(s, "found_z - empty pointer was found");
	if (ft_absi(a.x - b.x) >= ft_absi(a.y - b.y))
		persent = ((float)(current.x - ft_mini(a.x, b.x))) / (float)(ft_absi(a.x - b.x));
	else
		persent = ((float)(current.y - ft_mini(a.y, b.y))) / (float)(ft_absi(a.y - b.y));
	//fprint("persent %d\n", (int)(persent * 100));
	//if (sign.x * sign.y == -1)
	//	persent = (1 - persent);
	persent = persent * ft_absf(b.z - a.z);
	
	sign.z = 0;
	if (a.z < b.z)
	//if ()
		z = persent + a.z;
	else
		z = persent + b.z;
		//z = persent + b.z;
	return (z);
}
*/
void			draw_line(t_pos a, t_pos b, t_fdf *s)
{
	t_pos	delta;
	t_pos	sign;
	t_pos	current;
	int		error[2];

	if (!s)
		free_exit(s, "drow_line - empty pointer was found");
	current = a;
	delta.x = (int)ft_absi(b.x - a.x);
	delta.y = (int)ft_absi(b.y - a.y);
	//init_delta(&a, &b, &delta, s);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	//mlx_pixel_put(s->mlx, s->win, b.x, b.y, get_point_color(b.z, s));
	mlx_pixel_put(s->mlx, s->win, b.x, b.y, _get_color(current, a, b, delta));
	while (current.x != b.x || current.y != b.y)
	{
		//current.z = found_z(a, b, current, s, sign);
		//mlx_pixel_put(s->mlx, s->win, current.x, current.y, get_point_color(current.z, s));
		mlx_pixel_put(s->mlx, s->win, current.x, current.y, _get_color(current, a, b, delta));
		error[1] = error[0] * 2;
		logic(&current, &delta, &sign, error);
	}
}