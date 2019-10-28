/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:33:52 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/27 16:33:53 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	delete_lst(t_list **list)
{
	t_list	*tmp;
	t_list	*lst;

	if (!list)
		return ;
	lst = *list;
	while (lst)
	{
		if (lst->content)
			free(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	*list = NULL;
}

static void	delete_posi_arr(t_posi ***posi_arr, int size)
{
	t_posi	**arr;
	short	i;

	if (!posi_arr || !(*posi_arr))
		return ;
	arr = *posi_arr;
	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
	*posi_arr = NULL;
}

static void	delete_pos_arr(t_pos ***pos_arr, int size)
{
	t_pos	**arr;
	short	i;

	if (!pos_arr || !(*pos_arr))
		return ;
	arr = *pos_arr;
	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
	*pos_arr = NULL;
}

void		delete_arr(char ***char_arr)
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

void		free_exit(t_fdf *s, char *message)
{
	if (!s)
	{
		if (s->lst)
			delete_lst(&(s->lst));
		if (s->pos)
			delete_pos_arr(&(s->pos), s->arr_y_size);
		if (s->cpy)
			delete_posi_arr(&(s->cpy), s->arr_y_size);
		if (s->line)
			ft_strdel(&(s->line));
		if (s->read_till_end)
		{
			while (gnl(s->fd, &(s->line)) > 0)
				ft_strdel(&(s->line));
		}
		free(s);
	}
	if (message)
		fprint("ERROR: %s\n", message);
	exit(0);
}
