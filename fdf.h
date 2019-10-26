#ifndef FDF_H
# define FDF_H
# define BUFF_SIZE		10
# define FD_LIMIT		100
# define WIN_SIZE_HOR	1300
# define WIN_SIZE_VERT	1300
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

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>

typedef struct 	s_pos
{
	int		x;
	int		y;
	float	z;
	int		color;
}				t_pos;

typedef struct	s_fdf
{
	int		fd;
	int		color_exists;
	int		is_need_to_redraw;
	int		init_started;
	int		arr_x_size;
	int		arr_y_size;
	int		camera_x;
	int		camera_y;
	double	z_scale;
	double	scale;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	//float	max_z;
	//float	min_z;
	//float	angle;
	char	**arr;
	t_pos	**pos_arr;
	t_pos	**cpy_arr;
	t_pos	min;
	t_pos	max;
	char	*line;
	void	*mlx;
	void	*win;
}				t_fdf;

void		draw_line(t_pos a, t_pos b, t_fdf *s);	//	draw_line.c

void		delete_arr(char ***char_arr);		//	free_exit.c
void		delete_pos_arr(t_pos ***pos_arr);	//	free_exit.c
void		free_exit(t_fdf *s, char *message);	//	free_exit.c

int			gnl(int const fd, char **line);		//	gnl.c

void		start_calc(t_fdf *s);				//	start_calc.c

int			key_hook(int key, t_fdf *s);					//	hooks.c
int			mouse_hook(int param, int x, int y, t_fdf *s);	//	hooks.c
int			loop_hook(t_fdf *s);							//	hooks.c

void		read_file(t_fdf *s);				//	reader.c

void		iso_convert_array(t_fdf *s);  		//	redraw.c
void		set_minmax_z(t_fdf *s, float z);	//	redraw.c
void		redraw(t_fdf *s);					//	redraw.c

int			get_point_color(float z, t_fdf *s); /// rgb.c

void		x_rotation(int i, int j, t_fdf *s);

//int			get_red(float z, t_fdf *s);
//int			get_green(float z, t_fdf *s);
//int			get_blue(float z, t_fdf *s);

#endif