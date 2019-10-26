NAME		= fdf
FLAGS		= -Wall -Wextra -Werror -g 

# directories
DIR		=	./

# files
SRC			=	$(DIR)main.c					$(DIR)free_exit.c	\
				$(DIR)gnl.c						$(DIR)hooks.c		\
				$(DIR)reader.c					$(DIR)grafix_start.c\
				$(DIR)redraw.c					$(DIR)draw_line.c	\
				$(DIR)rgb.c
HEAD		= 	$(DIR)fdf.h
MLX			= 	mlx/libmlx.a -lmlx -framework OpenGL -framework AppKit

# libraries
L_FT 		= 	./libft/
L_FT_A 		= 	$(L_FT)libft.a

$(NAME) :
			@make -sC $(L_FT)
			@echo "Compiling fdf"
			@gcc $(FLAGS) $(SRC) $(L_FT_A) $(MLX) -o $(NAME)
			@echo "file $(NAME) was created succesfully"

clean :
			@echo "start cleaning"
			@make clean -sC $(L_FT)
			@rm -rf .DS_Store
			@rm -rf $(L_FT).DS_Store
			@echo "cleaning finished"

fclean : clean
			@rm -rf $(L_FT_A)
			@rm -rf $(NAME)
			@rm -rf $(NAME).dSYM

proj :
			@./$(NAME) test_maps/42.fdf #src.txt

all : 		$(NAME)

re: fclean all
