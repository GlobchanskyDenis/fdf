#include "fdf.h"
/*
void	y_rotation(int i, int j, t_fdf *s)
{
	t_pos	*dot;
	t_pos	old;

	if (!s)
		free_exit(s, "z_rotation - null pointer found\n");
	if (!(dot = &(s->pos[i][j])))
		free_exit(s, "z_rotation - null pointer returned\n");
	old = *dot;
	dot->y = old.y * cos(s->angle.z) + old.x * sin(s->angle.z);
	dot->x = old.x * cos(s->angle.z) - old.y * sin(s->angle.z);
}

void	y_rotation(int i, int j, t_fdf *s)
{
	t_pos	*dot;
	t_pos	old;

	if (!s)
		free_exit(s, "y_rotation - null pointer found\n");
	if (!(dot = &(s->pos[i][j])))
		free_exit(s, "y_rotation - null pointer returned\n");
	old = *dot;
	dot->x = old.x * cos(s->angle.y) + old.z * sin(s->angle.y);
	dot->z = old.z * cos(s->angle.y) - old.x * sin(s->angle.y);
}
*/
void	rotation(int i, int j, t_fdf *s)
{
	t_pos	*dot;
	t_pos	old;

	if (!s)
		free_exit(s, "rotation - null pointer found\n");
	if (!(dot = &(s->pos[i][j])))
		free_exit(s, "rotation - null pointer returned\n");
	if (s->angle.x != 0)
	{
		old = *dot;
		dot->y = old.y * cos(s->angle.x) + old.z * sin(s->angle.x);
		dot->z = old.z * cos(s->angle.x) - old.y * sin(s->angle.x);
	}
	if (s->angle.y != 0)
	{
		old = *dot;
		dot->x = old.x * cos(s->angle.y) + old.z * sin(s->angle.y);
		dot->z = old.z * cos(s->angle.y) - old.x * sin(s->angle.y);
	}
	if (s->angle.z != 0)
	{
		old = *dot;
		dot->y = old.y * cos(s->angle.z) + old.x * sin(s->angle.z);
		dot->x = old.x * cos(s->angle.z) - old.y * sin(s->angle.z);
	}
}