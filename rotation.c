#include "fdf.h"
/*
void	y_rotation(int i, int j, t_fdf *s)
{
	t_pos	**arr;
	t_pos	old;

	if (!s)
		free_exit(s, "x_rotation - null pointer found\n");
	if (!(arr = s->cpy_arr))
		free_exit(s, "x_rotation - null pointer returned\n");
	old.x = arr[i][j].x - s->camera_x;
	old.z = arr[i][j].z;
	//fprint("was %d %d\t\t", arr[i][j].y, (int)arr[i][j].z);
	arr[i][j].x = s->camera_x + (int)(((double)old.x) * cos(s->y_angle) + old.z * sin(s->y_angle));
	arr[i][j].z = (float)((-(double)old.x) * sin(s->y_angle) + old.z * sin(s->y_angle));
	//fprint("become %d %d\n", arr[i][j].y, (int)arr[i][j].z);
}
*/
void	x_rotation(int i, int j, t_fdf *s)
{
	t_pos	*dot;
	t_pos	old;

	if (!s)
		free_exit(s, "x_rotation - null pointer found\n");
	if (!(dot = &(s->pos[i][j])))
		free_exit(s, "x_rotation - null pointer returned\n");
	old = *dot;
	//fprint("was %d %d\t\t", arr[i][j].y, (int)arr[i][j].z);
	dot->y = old.y * cos(s->x_ang) + old.z * sin(s->x_ang);
	dot->z = old.z * cos(s->x_ang) - old.y * sin(s->x_ang);
	//fprint("become %d %d\n", arr[i][j].y, (int)arr[i][j].z);
}