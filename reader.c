/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:32:27 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/27 16:35:14 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		extract_color(char *str, t_fdf *s)
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

static t_pos	make_pos(char *str, int x, int y, t_fdf *s)
{
	t_pos	pos;
	int		int_z;

	if (!str || !s)
		free_exit(s, "make_pos - null pointer found");
	ft_bzero(&pos, sizeof(t_pos));
	pos.x = (double)x - ((double)s->arr_x_size - 1) / 2;
	pos.y = (double)y - ((double)s->arr_y_size - 1) / 2;
	int_z = ft_atoi(str);
	if (!(s->line = ft_itoa(int_z)))
		fprint("mad itoa\n");
	else
	{
		if (ft_strchr(str, ','))
			pos.color = extract_color(ft_strchr(str, ','), s);
		else if (strcmp(s->line, str))
			free_exit(s, "bad string");
		ft_strdel(&(s->line));
		pos.z = (double)int_z;
	}
	set_minmax_xy(pos, s);
	set_minmax_z(pos.z, s);
	return (pos);
}

static t_pos	*make_pos_arr(char *str, int i, t_fdf *s)
{
	t_pos	*dst;
	char	**char_arr;
	int		j;

	if (!str || !s)
		free_exit(s, "make_pos_arr - null pointer found");
	if (!(dst = (t_pos *)malloc(sizeof(t_pos) * s->arr_x_size)))
		free_exit(s, "make_pos_2arr - malloc returned null");
	ft_bzero(dst, sizeof(t_pos) * s->arr_x_size);
	if (!(char_arr = ft_strsplit(str, ' ')))
	{
		delete_arr(&char_arr);
		free_exit(s, "make_pos_2arr - cannot split char string");
	}
	j = -1;
	while (++j < s->arr_x_size)
		dst[j] = make_pos(char_arr[j], j, i, s);
	delete_arr(&char_arr);
	return (dst);
}

static t_pos	**make_pos_2arr(t_list *lst, t_fdf *s)
{
	t_pos	**dst;
	int		i;

	if (!lst || !s)
		free_exit(s, "make_pos_2arr - null pointer returned");
	if (!(dst = (t_pos **)malloc(sizeof(t_pos *) * (s->arr_y_size + 1))))
		free_exit(s, "make_pos_2arr - malloc returned null");
	ft_bzero(dst, sizeof(t_pos *) * (s->arr_y_size + 1));
	i = -1;
	while (++i < s->arr_y_size)
	{
		if (!lst)
			free_exit(s, "make_pos_2arr - null node found");
		if (!(dst[i] = make_pos_arr(lst->content, i, s)))
			free_exit(s, "make_pos_2arr - malloc returned null");
		lst = lst->next;
	}
	dst[i] = NULL;
	return (dst);
}

void			read_file(t_fdf *s)
{
	t_list	*lst;
	char	*line;

	if (!s)
		free_exit(s, "read_file - empty pointer found");
	if (!(lst = ft_lstnew_fag(NULL, 0)))
		free_exit(s, "read_file - cannot create node");
	s->lst = lst;
	while (gnl(s->fd, &line) > 0)
	{
		if (s->arr_x_size == 0)
			s->arr_x_size = (int)ft_countwords(line, ' ');
		else if (s->arr_x_size != (int)ft_countwords(line, ' '))
			free_exit(s, "read_file - source lines have different length");
		lst->content = line;
		if (!(lst->next = ft_lstnew_fag(NULL, 0)))
			free_exit(s, "read_file - cannot create node");
		lst = lst->next;
		s->arr_y_size++;
	}
	if (!(s->pos = make_pos_2arr(s->lst, s)))
		free_exit(s, "read_file - cannot create pos_arr");
}
