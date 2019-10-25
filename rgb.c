#include "fdf.h"

int		get_red(float z, t_fdf *s)
{
	float	persent;

	if (!s)
		free_exit(s, "get_red - empty pointer found");
	if (z > 0 && z > s->max_z / 5)
	{
		persent = (z - s->max_z / 5) / (s->max_z) + 0.2;
		//persent = (z - s->max_z / 5) / (s->max_z * 4 / 5);
		//persent = z / s->max_z;
		//if (z > s->max_z)
			//fprint("wrong max z\n");
		return ((int)((float)255 * persent));
	}
	return (0);
}

int		get_green(float z, t_fdf *s)
{
	float	persent;
	float	min_z;

	if (!s)
		free_exit(s, "get_green - empty pointer found");
	if (z > 0 && z < s->max_z * 4 / 5)
	{
		persent = z / (s->max_z * 4 / 5);
		return ((int)((float)255 * (1 - persent)));
	}
	if (z == 0)
			return (255);
	if (z < 0 && z > s->min_z / 3)
	{
		min_z = - s->min_z;
		z = -z;
		persent = 1 - z / (min_z / 3);
		//persent = persent / 2 + min_z / 2;
		return ((int)((float)255 * persent));
	}
	return (0);
}

int		get_blue(float z, t_fdf *s)
{
	float	persent;
	float	min_z;

	if (!s)
		free_exit(s, "get_blue - empty pointer found");
	/*
	if (z < 0 && z <= s->min_z / 2)
	{
		min_z = -(s->min_z);
		z = -z;
		persent = (1 - z / min_z) * 2;
		//persent = persent * 0.9 + min_z / 10;
		return ((int)((float)255 * persent));
	}
	if (z < 0 && z > s->min_z / 2)
	{
		min_z = -(s->min_z);
		z = -z;
		persent = z * 2 / min_z;
		//persent = persent * 0.9 + min_z / 10;
		return ((int)((float)255 * persent));
	}
	*/
	if (z < 0)
	{
		min_z = -(s->min_z);
		z = -z;
		persent = z / min_z;
		//persent = persent * 0.9 + min_z / 10;
		return ((int)((float)255 * persent));
	}
	return (0);
}