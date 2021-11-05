# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/21 20:02:11 by fbes          #+#    #+#                  #
#    Updated: 2021/11/05 21:59:50 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		fdf

SRCS =		main.c map.c window.c setup.c drawer.c debug.c \
			config_reader.c config_checker.c config_parser.c \
			convert.c renderer.c controls.c

INCLUDES =	-I lib/libft -I includes -I lib/mlx

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-fsanitize=address

all: $(NAME)

$(NAME): $(OBJS) lib/libft/libft.a libmlx.dylib
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
	make -C lib/mlx clean

fclean:
	rm -f $(OBJS) $(NAME)
	make -C lib/libft fclean
	make -C lib/mlx clean
	rm -f libmlx.dylib

re: fclean all

.PHONY: all clean fclean re bonus
