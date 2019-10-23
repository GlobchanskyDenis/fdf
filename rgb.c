int		get_red(float z, t_fdf *s)
{
	float	persent;

	if (!s)
		free_exit(s, "get_red - empty pointer found");
	if (z > 0 && z > max_z / 3)
	{
		persent = (z - max_z / 3) / (max_z * 2 / 3);
		return ((int)((float)256 * persent));
	}
	return (0);
}

int		get_green(float z, t_fdf *s)
{
	float	persent;

	if (!s)
		free_exit(s, "get_green - empty pointer found");
	if (z > 0 && z < max_z * 2 / 3)
	{
		persent = z / (max_z * 2 / 3);
		return ((int)((float)256 * (1 - persent)));
	}
	return (0);
}

int		get_blue(float z, t_fdf *s)
{
	if (!s)
		free_exit(s, "get_blue - empty pointer found");
	if (z < 0)
	{
		persent = -z / (-min_z);
		return ((int)((float)256 * (1 - persent)));
	}
	return (0);
}