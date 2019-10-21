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
	{
		fprint("cannot open file\n");
		free(s);
		return (NULL);
	}
	if (read(s->fd, &buf_ch, 0) < 0)
	{
		fprint("cannot take access to %s\n", av[1]);
		free(s);
		return (NULL);
	}
	return (s);
}

int				main(int ac, char **av)
{
	t_fdf	*s;

	if (ac != 2 || !av)
		return (wrong_params(ac, av));
	if (!(s = create_fdf_struct(av)))
		return (1);
	read_file(s);
	//loop(s);
	free_exit(s, NULL);
	return (0);
}