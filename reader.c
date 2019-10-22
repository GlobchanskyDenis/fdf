#include "fdf.h"

int		extract_color(char *str, t_fdf *s)
{
	int		color;

	if (!str || !s)
		free_exit(s, "extract_color null pointer found");
	s->color_exists = 1;
	str++;
	if (str[0] == '0' && str[1] == 'x')
		color = ft_atoi_base((str + 2), 16);
	else if (str[0] == '0' && str[1] == 'o')
		color = ft_atoi_base((str + 2), 8);
	else if (str[0] == '0' && str[1] == 'b')
		color = ft_atoi_base((str + 2), 2);
	else
		color = atoi(str);
	return (color);
}

t_pos	**make_bigger_pos_arr(t_pos **old_arr, t_pos *new_element)
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
	if (!(dst = (t_pos **)malloc(sizeof(t_pos *) * (arr_len + 2))))
		return (NULL);
	dst[arr_len] = new_element;
	dst[arr_len + 1] = NULL;
	while (--arr_len >= 0)
		dst[arr_len] = old_arr[arr_len];
	free(old_arr);
	//fprint("new t_pos array\n");
	return (dst);
}

t_pos	make_pos(char *str, int x, int y, t_fdf *s)
{
	t_pos	pos;
	char	*tmp;

	if (!str || !s)
		free_exit(s, "make_pos - null pointer found");
	ft_bzero(&pos, sizeof(t_pos));
	pos.x = x;
	pos.y = y;
	pos.z = ft_atoi(str);
	if (!(tmp = ft_itoa(pos.z)))
		fprint("mad itoa\n");
	else
	{
		if (strcmp(tmp, str) && ft_strchr(str, '.'))
			pos.color = extract_color(ft_strchr(str, '.'), s);
		else if (strcmp(tmp, str))
		{
			//fprint("tmp %s\nstr %s\n", tmp, str);
			ft_strdel(&tmp);
			free_exit(s, "bad string");
		}
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
	i = -1;
	while (char_arr[++i])
		arr[i] = make_pos(char_arr[i], i + 1, y, s);
	s->arr_y_size = i + 1;
	return (arr);
}

void	read_file(t_fdf *s)
{
	if (!s)
		return ;
	if (!(s->pos_arr = (t_pos **)malloc(sizeof(t_pos *))))
		free_exit(s, "read file - malloc returned null");
	ft_bzero(s->pos_arr, sizeof(t_pos));
	while(gnl(s->fd, &(s->line)))
	{
		if (!(s->arr = ft_strsplit(s->line, ' ')))
			free_exit(s, "read file - null pointer returned");
		if (s->arr_x_size == 0)
			s->arr_x_size = (int)count_words(s->arr);
		if (s->arr_x_size != (int)count_words(s->arr))
			free_exit(s, "source lines have different length");
		if (!(s->pos_arr = make_bigger_pos_arr(s->pos_arr, 
				make_pos_arr(s->arr, s->arr_y_size, s))))
			free_exit(s, "read file - null pointer in position returned");
		delete_arr(&(s->arr));
		ft_strdel(&(s->line));
		s->arr_y_size++;
	}
}