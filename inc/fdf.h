#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h> 
#include <math.h>
#include "../libft/libft.h"
#include "../ft_printf/printf.h"
#include "get_next_line.h"
#include <MLX42/MLX42.h>

#define WIDTH 700
#define HEIGHT 700
#define BUFFER_SIZE 1000

typedef struct point {
	int x;
	int y;
	int z;
}		t_point;

typedef struct data {
	t_point **points;
	t_point **converted_points;
	int col_len;
	int row_len;
	int zoom;
	mlx_t       *mlx;
    mlx_image_t *img;
}		t_data;
