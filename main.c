#include "fdf.h"

static int		wrong_params(int ac, char **av)
{
	if (ac > 2)
		fprint("./fdf <filename> - too many parameters\n");
	else if (ac < 2)
		fprint("./fdf <filename> - too few parameters\n");
	if (!av)
		fprint("empty pointer av\n");
	return (0);
}

static t_fdf	*create_fdf_struct(char **av)
{
	t_fdf	*s;
	char	buf_ch;

	if (!av)
		return (NULL);
	if (!(s = (t_fdf *)malloc(sizeof(t_fdf))))
		return (NULL);
	ft_bzero(s, sizeof(t_fdf));
	if ((s->fd = open(av[1], O_RDONLY)) < 3)
		free_exit(s, "cannot open file");
	/*
	{
		fprint("cannot open file\n");
		free(s);
		return (NULL);
	}
	*/
	if (read(s->fd, &buf_ch, 0) < 0)
	{
		fprint("cannot take access to %s\n", av[1]);
		free_exit(s, NULL);
	}
	/*
	{
		fprint("cannot take access to %s\n", av[1]);
		free(s);
		return (NULL);
	}
	*/
	return (s);
}


void			tmp_write_pos_arr(t_fdf *s, t_pos **arr)
{
	t_pos	*tab;
	int		i;
	int		j;

	if (!s)
		return ;
	i = 0;
	while (arr[i])
	{
		tab = arr[i];
		j = 0;
		while (j < s->arr_x_size)
		{
			fprint("%d %d %d\t\t", tab[j].x, tab[j].y, (int)tab[j].z);
			j++;
		}
		fprint("\n");
		i++;
	}
}


void			loop(t_fdf *s)
{
	if (!s)
		free_exit(s, "loop - null pointer found");
	fprint("=== grafix start ===\n");
	start_calc(s);
	//tmp_write_pos_arr(s, s->cpy_arr);
	//create_images();
	if (!(s->mlx = mlx_init()) || !(s->win = mlx_new_window(s->mlx, WIN_SIZE_HOR, WIN_SIZE_VERT, "fdf by bsabre-c")))
		free_exit(s, "loop - error in opening window");
	mlx_loop_hook(s->mlx, loop_hook, s);
	mlx_key_hook(s->win, key_hook, s);
	mlx_mouse_hook(s->win, mouse_hook, s);
	mlx_loop(s->mlx);
}

int				main(int ac, char **av)
{
	t_fdf	*s;

	if (ac != 2 || !av)
		return (wrong_params(ac, av));
	if (!(s = create_fdf_struct(av)))
		free_exit(s, "create_fdf_struct returned null");
	read_file(s);
	//tmp_write_pos_arr(s, s->pos_arr);
	fprint("arr x size %d\n arr y size %d\n", s->arr_x_size, s->arr_y_size);
	loop(s);
	free_exit(s, NULL);
	return (0);
}