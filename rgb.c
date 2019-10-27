#include "fdf.h"

static int	get_red(double z, t_fdf *s)
{
	double	persent;

	if (!s)
		free_exit(s, "get_red - empty pointer found");
	if (z > 0 && z > s->max.z / 5)
	{
		persent = (z - s->max.z / 5) / (s->max.z) + 0.2;
		return ((int)((double)255 * persent));
	}
	return (0);
}

static int	get_green(double z, t_fdf *s)
{
	double	persent;
	double	min_z;

	if (!s)
		free_exit(s, "get_green - empty pointer found");
	if (z > 0 && z < s->max.z * 4 / 5)
	{
		persent = z / (s->max.z * 4 / 5);
		return ((int)((double)255 * (1 - persent)));
	}
	if (z == 0)
			return (255);
	if (z < 0 && z > s->min.z / 3)
	{
		min_z = - s->min.z;
		z = -z;
		persent = 1 - z / (min_z / 3);
		return ((int)((double)255 * persent));
	}
	return (0);
}

static int	get_blue(double z, t_fdf *s)
{
	double	persent;
	double	min_z;

	if (!s)
		free_exit(s, "get_blue - empty pointer found");
	if (z < 0)
	{
		min_z = -(s->min.z);
		z = -z;
		persent = z / min_z;
		return ((int)((double)255 * persent));
	}
	return (0);
}

int			get_point_color(double z, t_fdf *s)
{
	int		r;
	int		g;
	int		b;

	if (!s)
		free_exit(s, "get_point_color - null pointer found");
	r = get_red(z, s);
	g = get_green(z, s);
	b = get_blue(z, s);
	return ((r << 16) | (g << 8) | b);
}