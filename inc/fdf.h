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

void    put_line(mlx_image_t *img, int x1, int y1, int x2, int y2);
void    draw_lines(mlx_image_t *img, t_data *data, t_point **points);
void    apply_center(t_data *data);
void    apply_isometric(t_data *data);
void    apply_zoom(t_data *data, int zoom);
void    set_original_point_values(t_data *data);
void    zoom_image(t_data *data, int zoom);
void    remove_isometric(t_data *data);
void    add_z(t_data *data, int val);
void    increment_z(t_data *data, int val);
void    render_data(t_data *data);
void 	my_keyhook(mlx_key_data_t keydata, void* param);

