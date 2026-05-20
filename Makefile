NAME = fdf
OBJ = main.o
INC = -I inc
CFLAGS =  
LIBFT = libft/libft.a
LIBH = libft/libft.h
LIBS = MLX42/build/libmlx42.a -lglfw -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

%.o: $(addprefix ./src/,%.c)
	@gcc $(CFLAGS) $(INC) -IMLX42/include -c $< $(LIBH)

$(NAME): $(OBJ)
	@gcc -g $(CFLAGS) $(OBJ) $(LIBS) $(LIBFT) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all
