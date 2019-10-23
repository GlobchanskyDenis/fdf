#include "fdf.h"

static void	init_delta(t_pos *a, t_pos *b, t_pos *delta, t_fdf *s)
{
	if (!a || !b || !delta || !s)
		free_exit(s, "drow_line - empty pointer was found");
	delta->x = (int)ft_absi(b->x - a->x);
	delta->y = (int)ft_absi(b->y - a->y);
}

static void	logic(t_pos *a, t_pos *delta, t_pos *sign, int *error)
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

static int	get_gradient_color(t_pos a, t_pos b, t_pos current, t_fdf *s)
{
	float	persent;
	int		red;
	int		green;
	int		blue;

	if (!s)
		free_exit(s, "get_gradient_color - empty pointer was found");
	if (ft_absi(a.x - b.x) > ft_absi(a.y - b.y))
		persent = ((float)current.x - (float)ft_mini(a.x, b.x)) / \
			((float)ft_absi((int)(a.z - b.z)));
	else
		persent = ((float)current.y - (float)ft_mini(a.y, b.y)) / \
			((float)ft_absi((int)(a.z - b.z)));
	red = get_red((persent * (float)ft_absi((int)(a.z - b.z))), s);
	green = get_green((persent * (float)ft_absi((int)(a.z - b.z))), s);
	blue = get_blue((persent * (float)ft_absi((int)(a.z - b.z))), s);
	return ((red << 16) | (green << 8) | blue);
}

void		draw_line(t_pos a, t_pos b, int color, t_fdf *s)
{
	t_pos	delta;
	t_pos	sign;
	int		error[2];

	if (!s)
		free_exit(s, "drow_line - empty pointer was found");
	init_delta(&a, &b, &delta, s);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	mlx_pixel_put(s->mlx, s->win, b.x, b.y, color);
	while (a.x != b.x || a.y != b.y)
	{
		mlx_pixel_put(s->mlx, s->win, a.x, a.y, color);
		error[1] = error[0] * 2;
		logic(&a, &delta, &sign, error);
	}
}