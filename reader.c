#include "fdf.h"

int		extract_color(char *str)
{
	int		dst;

	if (!str)
		return (0);
	
}

t_pos	**make_bigger_array(t_pos **old_arr, t_pos *new_element)
{
	int		arr_len;
	t_pos	**dst;

	if (!old_arr || !new_element)
	{
		delete_pos_arr(&old_arr);
		if (new_element)
			free(new_element);
		return (NULL);
	}
	arr_len = 0;
	while (old_arr[arr_len])
		arr_len++;
	if (!(dst = (t_pos)malloc(sizeof(t_pos *) * (arr_len + 2))))
		return (NULL);
	dst[arr_len] = new_element;
	dst[arr_len + 1] = NULL;
	while (--arr_len >= 0)
		dst[arr_len] = old_arr[arr_len];
	free(old_arr);
	fprint("new t_pos array\n");
	return (dst);
}

t_pos	make_pos(char *str, int x, int y)
{
	t_pos	pos;
	char	*tmp;

	ft_bzero(&pos, sizeof(t_pos));
	pos.x = x;
	pos.y = y;
	if (!str)
		return (t_pos);
	pos.z = ft_atoi(str);
	if (!(tmp = ft_itoa(pos.z))
		fprint("mad itoa\n");
	else
	{
		if (strcmp(tmp, str) && )
			pos.color = extract_color(str);
		ft_strdel(&tmp);
	}
	return (pos);
}

t_pos	*make_pos_arr(char **char_arr, int y, t_fdf *s)
{
	t_pos	*arr;
	int	i;

	if (!char_arr || !s)
		free_exit(s, "read file - null pointer returned");
	if (!(arr = (t_pos *)malloc(sizeof(t_pos) * s->arr_x_size)))
		free_exit(s, "make_pos_arr - malloc returned null");
	i = 0;
	while (char_arr[i])
		arr[i] = make_pos(char_arr[i++], i + 1, y);
	return (arr);
}

void	read_file(t_fdf *s)
{
	if (!s)
		return ;
	if (!(s->pos_arr = (t_pos *)malloc(sizeof(t_pos) * 2)))
		free_exit(s, "read file - malloc returned null");
	ft_bzero(s->pos_arr, sizeof(t_pos));
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