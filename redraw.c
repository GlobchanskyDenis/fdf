#include "fdf.h"

void		redraw(t_fdf *s)
{
	if (!s)
		free_exit(s, "redraw - empty pointer found");
	
}

void		set_minmax_z(t_fdf *s, int z)
{
	if (!s)
		free_exit(s, "set_minmax_z - empty pointer found");
	if (s->init_started)
	{
		if (s->max_z < z)
			s->max_z = z;
		if (s->min_z > z)
			s->min_z = z;
	}
	else
	{
		s->max_z = z;
		s->min_z = z;
		s->init_started = 1;
	}
}