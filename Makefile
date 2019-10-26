# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: forange- <forange-@student.fr.42>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/26 13:58:12 by forange-          #+#    #+#              #
#    Updated: 2019/10/26 15:12:34 by forange-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
FLAGS		= -Wall -Wextra -Werror -g

# directories
DIR_O		=	objects

# files
SRC			=	main.c			free_exit.c		\
				gnl.c			hooks.c			\
				reader.c		grafix_start.c	\
				redraw.c		draw_line.c		\
				rgb.c

OBJ			=	$(addprefix $(DIR_O)/,$(SRC:.c=.o))

MLX			= 	-L./mlx -lmlx -framework OpenGL -framework AppKit

# libraries
L_FT_D 		= 	./libft
L_FT_L 		= 	$(L_FT_D)/libft.a

.PHONY: all clean fclean re proj

$(NAME) : $(OBJ)
			@make -sC $(L_FT_D)
			@echo "Compiling fdf"
			@gcc $(FLAGS) $(OBJ) $(L_FT_L) $(MLX) -o $(NAME)
			@echo "File $(NAME) was created succesfully"

$(DIR_O)/%.o: %.c fdf.h
			@mkdir -p $(DIR_O)
			@gcc $(FLAGS) -o $@ -c $<

clean :
			@echo "Start cleaning"
			@make clean -sC $(L_FT_D)
			@rm -rf .DS_Store
			@rm -rf $(L_FT_D)/.DS_Store
			@rm -rf $(DIR_O)
			@echo "Cleaning finished"

fclean : clean
			@rm -rf $(L_FT_L)
			@rm -rf $(NAME)
			@rm -rf $(NAME).dSYM

proj :
			@./$(NAME) test_maps/42.fdf #src.txt

all : 		$(NAME)

re: fclean all
