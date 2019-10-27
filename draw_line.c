#include "fdf.h"

static int		get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

static double	percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

static int		get_color(t_posi current, t_posi start, t_posi end, t_posi delta)
{
    int     red;
    int     green;
    int     blue;
    double  percentage;

    if (current.color == end.color)
        return (current.color);
    if (delta.x > delta.y)
        percentage = percent(start.x, end.x, current.x);
    else
        percentage = percent(start.y, end.y, current.y);
    red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
    green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
    blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
    return ((red << 16) | (green << 8) | blue);
}

static void		logic(t_posi *a, t_posi *delta, t_posi *sign, int *error)
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

void			draw_line(t_posi a, t_posi b, t_fdf *s)
{
	t_posi	delta;
	t_posi	sign;
	t_posi	current;
	int		error[2];

	if (!s)
		free_exit(s, "drow_line - empty pointer was found");
	current = a;
	delta.x = (int)ft_absi(b.x - a.x);
	delta.y = (int)ft_absi(b.y - a.y);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	mlx_pixel_put(s->mlx, s->win, b.x + s->shift_x, \
		b.y + s->shift_y, get_color(current, a, b, delta));
	while (current.x != b.x || current.y != b.y)
	{
		mlx_pixel_put(s->mlx, s->win, current.x + s->shift_x, \
			current.y + s->shift_y, get_color(current, a, b, delta));
		error[1] = error[0] * 2;
		logic(&current, &delta, &sign, error);
	}
}