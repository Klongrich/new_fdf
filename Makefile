NAME = fdf
OBJ = main.o get_next_line.o draw.o convert_data.o handle_keys.o
INC = -I inc
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a
LIBH = libft/libft.h
FT_PRINTF = ft_printf/libftprintf.a
FT_PRINTF_H = ft_printf/printf.h
LIBS = MLX42/build/libmlx42.a -lglfw -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

%.o: $(addprefix ./src/,%.c)
	@gcc $(CFLAGS) $(INC) -IMLX42/include -c $< $(LIBH) $(FT_PRINTF_H)

$(NAME): $(OBJ)
	@gcc -g $(CFLAGS) $(OBJ) $(LIBS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all
