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