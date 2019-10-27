/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:33:04 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/27 16:33:06 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (read(s->fd, &buf_ch, 0) < 0)
	{
		fprint("cannot take access to %s\n", av[1]);
		free_exit(s, NULL);
	}
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
	while (i < s->arr_y_size)
	{
		tab = arr[i];
		j = 0;
		while (j < s->arr_x_size)
		{
			fprint("%d %d\t%d\t", (int)(tab[j].x * 10),
				(int)(tab[j].y * 10), (int)tab[j].z);
			j++;
		}
		fprint("\n");
		i++;
	}
}

static void		loop(t_fdf *s)
{
	if (!s)
		free_exit(s, "loop - null pointer found");
	start_calc(s);
	if (!(s->mlx = mlx_init()) || \
		!(s->win = mlx_new_window(s->mlx, WIN_SIZE_HOR, WIN_SIZE_VERT, "fdf by bsabre-c")))
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
	//tmp_write_pos_arr(s, s->pos);
	//fprint("arr x_size %d y_size %d\n", s->arr_x_size, s->arr_y_size);
	//fprint("min xyz\t%d\t%d\t%d\n", (int)s->min.x, (int)s->min.y, \
	//	(int)s->min.z);
	//fprint("max xyz\t%d\t%d\t%d\n", (int)s->max.x, (int)s->max.y, \
	//	(int)s->max.z);
	loop(s);
	free_exit(s, NULL);
	return (0);
}
