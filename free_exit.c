#include "fdf.h"

void	delete_pos_arr(t_pos ***pos_arr)
{
	t_pos	**arr;
	short	i;

	if (!pos_arr || !(*pos_arr))
		return ;
	arr = *pos_arr;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	*pos_arr = NULL;
}

void	delete_arr(char ***char_arr)
{
	char	**arr;
	short	i;

	if (!char_arr || !(*char_arr))
		return ;
	arr = *char_arr;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	*char_arr = NULL;
}

void	free_exit(t_fdf *s, char *message)
{
	if (!s)
	{
		if (s->arr)
			delete_arr(&(s->arr));
		if (s->pos_arr)
			delete_pos_arr(&(s->pos_arr));
		if (s->cpy_arr)
			delete_pos_arr(&(s->cpy_arr));
		if (s->line)
			ft_strdel(&(s->line));
		if (s->win)
			s->win = NULL;
		if (s->mlx)
			s->mlx = NULL;
		free(s);
	}
	if (message)
		fprint("ERROR: %s\n", message);
	exit(0);
}