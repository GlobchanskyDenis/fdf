#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"

typedef struct 	s_pos
{
	int		x;
	int		y;
	int		z;
	int		color;
}				t_pos;

typedef struct	s_fdf
{
	int		fd;
	int		color_exists;
	int		arr_x_size;
	int		arr_y_size;
	char	**arr;
	t_pos	*pos_arr;
	char	*line;
	void	*mlx;
	void	*win;
}				t_fdf;

void		read_file(t_fdf *s);
void		free_exit(t_fdf *s, char *message);
void		delete_arr(char ***char_arr);
void		delete_pos_arr(t_pos ***pos_arr);

#endif