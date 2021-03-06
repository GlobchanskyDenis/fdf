/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:36:30 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/28 14:36:33 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFF_SIZE		10
# define FD_LIMIT		100
# define WIN_SIZE_HOR	900
# define WIN_SIZE_VERT	900
# define ESCAPE			53
# define BLUE			0x0000FF
# define RED			0xFF0000
# define GREEN			0x00FF00
# define WHITE			0xFFFFFF
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define KEY_UP			126
# define KEY_DOWN		125
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_PLUS		69
# define KEY_MINUS		78
# define KEY_X			7
# define KEY_Y			16
# define KEY_Z			6
# define KEY_P			35
# define Z_SCALE		1.1
# define TRUE_ISO		1
# define ISO			0

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>

typedef struct	s_pos
{
	double	x;
	double	y;
	double	z;
	int		color;
}				t_pos;

typedef struct	s_posi
{
	int		x;
	int		y;
	int		color;
}				t_posi;

typedef struct	s_fdf
{
	int		fd;
	int		projection;
	int		read_till_end;
	int		color_exists;
	int		is_need_to_redraw;
	int		init_flag;
	t_list	*lst;
	char	*line;
	int		arr_x_size;
	int		arr_y_size;
	int		shift_x;
	int		shift_y;
	double	scale;
	t_pos	**pos;
	t_posi	**cpy;
	t_pos	angle;
	t_pos	min;
	t_pos	max;
	void	*mlx;
	void	*win;
}				t_fdf;

void			draw_line(t_posi a, t_posi b, t_fdf *s);
void			delete_arr(char ***char_arr);
void			free_exit(t_fdf *s, char *message);
int				gnl(int const fd, char **line);
void			set_minmax_xy(t_pos pos, t_fdf *s);
void			set_minmax_z(double z, t_fdf *s);
void			start_calc(t_fdf *s);
int				key_hook(int key, t_fdf *s);
int				mouse_hook(int param, int x, int y, t_fdf *s);
int				loop_hook(t_fdf *s);
void			read_file(t_fdf *s);
void			iso_convert_array(t_fdf *s);
void			draw_menu(t_fdf *s);
void			redraw(t_fdf *s);
int				get_point_color(double z, t_fdf *s);
t_pos			rotation(int i, int j, t_fdf *s);
void			z_decrease(t_pos **arr, t_fdf *s);
void			z_increase(t_pos **arr, t_fdf *s);

#endif
