# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/21 20:02:11 by fbes          #+#    #+#                  #
#    Updated: 2021/11/11 18:54:47 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		fdf

SRCS =		src/main.c src/map.c src/window.c src/setup.c src/drawer.c \
			src/debug.c src/colors.c src/config_reader.c src/config_checker.c \
			src/config_parser.c src/convert.c src/bresenham.c src/renderer.c \
			src/renderer_checks.c src/keys.c src/controls.c

HEADERS =	includes/fdf.h includes/fdf_drawer.h includes/fdf_parser.h \
			includes/fdf_settings.h includes/fdf_structs.h

INCLUDES =	-I lib/libft -I includes -I lib/mlx

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) lib/libft/libft.a libmlx.dylib
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) \
	lib/libft/libft.a libmlx.dylib -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

lib/libft/libft.a:
	make -C lib/libft

libmlx.dylib:
	make -C lib/mlx
	test -L libmlx.dylib || ln -sf lib/mlx/libmlx.dylib libmlx.dylib

bonus: all

clean:
	rm -f $(OBJS)
	make -C lib/libft clean

fclean:
	rm -f $(OBJS) $(NAME)
	make -C lib/libft fclean
	make -C lib/mlx clean
	rm -f libmlx.dylib

re: fclean all

.PHONY: all clean fclean re bonus
