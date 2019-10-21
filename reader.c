#include "fdf.h"

t_pos	**make_bigger_array(t_pos **old_arr, t_pos *new_element)
{
	if (!old_arr || !new_element)
	{
		/////////
	}
}

t_pos	make_pos(char *str, short y)
{
	////////
}

t_pos	*make_pos_arr(char **char_arr, short y, t_fdf *s)
{
	t_pos	*arr;
	short	i;

	if (!char_arr || !s)
		free_exit(s, "read file - null pointer returned");
	if (!(arr = (t_pos *)malloc(sizeof(t_pos) * s->arr_x_size)))
		free_exit(s, "make_pos_arr - malloc returned null");
	i = 0;
	while (char_arr[i])
		arr[i] = make_pos(char_arr[i++], y);
	////////
}

void	read_file(t_fdf *s)
{
	if (!s)
		return ;
	if (!(s->pos_arr = (t_pos *)malloc(sizeof(t_pos) * 2)))
		free_exit(s, "read file - malloc returned null");
	ft_bzero(s->pos_arr, 2 * sizeof(t_pos));
	while(gnl(s->fd, &(s->line)))
	{
		if (!(s->arr = ft_strsplit(s->line, '-')))
			free_exit(s, "read file - null pointer returned");
		if (s->arr_x_size == 0)
			s->arr_x_size = countwords(s->arr);
		if (s->arr_x_size != countwords(s->arr))
			free_exit(s, "source lines have different length");
		if (!(s->pos_arr = make_bigger_pos_arr(s->pos_arr, 
				make_pos_arr(s->arr, s->arr_y_size, s))))
			free_exit(s, "read file - null pointer in position returned");
		delete_arr(&(s->arr));
		ft_strdel(&(s->line));
		s->arr_y_size++;
	}
}