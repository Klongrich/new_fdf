#include "fdf.h"

int		contains_number(char *str) {
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i]) {
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		get_rowlen(char	*row) {
	char **temp;
	int i;

	i = 0;
	temp = ft_strsplit(row, ' ');
	while (temp[i]) {
		printf("temp: %s\n", temp[i]);
		if (!contains_number(temp[i]))
			return (-1);
		i++;
	}
	free(temp);
	return (i);
}

int	print_error(int e) {
	if (e == -1)
		ft_printf("file does not contain all numbers\n");
	else
		ft_printf("Row sizes are not the same\n");
	return (0);
}


int		verify_file(char *file_path, t_data *data)
{
	int fd;
	char *str;
	int	row_len;
	int i;

	i = 0;
	row_len = 0;
	fd = open(file_path, O_RDONLY, S_IRUSR);
	if (fd == -1)
		ft_printf("error opening file\n");
	else
	{
		while(get_next_line(fd, &str))
		{
			printf("reading file\n");
			if (i == 0)
			{
				row_len = get_rowlen(str);
				if (row_len == -1)
				{
					close(fd);
					free(str);
					printf("error -1\n");
					return (-1);
				}
					
			}
			if (row_len != get_rowlen(str))
			{
				printf("row_len error\n");
				close(fd);
				free(str);
				return(print_error(get_rowlen(str)));
			}
			i++;
			printf("i: %d; str: %s\n", i, str);
			free(str);
		}
	}
	data->col_len = i;
	data->row_len = row_len;
	close(fd);
	return (1);
}

void	init_point(t_point *point) {
	point->x = 0;
	point->y = 0;
	point->z = 0;
}
void	create_tpoints(char *str, t_data *data, int y)
{
	int i;
	char **temp;
	t_point point;

	i = 0;
	temp = ft_strsplit(str, ' ');
	while (temp[i])
	{
		init_point(&point);
		point.y = y;
		point.x = i;
		point.z = ft_atoi(temp[i]);
		data->points[y][i] = point;
		data->converted_points[y][i] = point;
		i++;
	}
}

void	print_points(t_data *data, int print_converted) {
	int i;
	int y;

	i = 0;
	y = 0;
	while (i < data->col_len)
	{
		y = 0;
		while (y < data->row_len)
		{
			if (print_converted)
				printf("(x, y, z) -> (%d, %d, %d)\n", data->converted_points[i][y].x, data->converted_points[i][y].y, data->converted_points[i][y].z);
			else
				printf("(x, y, z) -> (%d, %d, %d)\n", data->points[i][y].x, data->points[i][y].y, data->points[i][y].z);
			y++;
		}
		i++;
	}
}


void	apply_center(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->col_len)
	{
		j = 0;
		while (j < data->row_len)
		{
			data->points[i][j].x += (WIDTH / 2);
			data->points[i][j].y += (HEIGHT / 2);
			data->points[i][j].z += (HEIGHT / 2);
			j++;
		}
		i++;
	}

}

void	apply_isometric(t_data *data) {
	int i;
	int j;
	int x;

	x = 0;
	i = 0;
	while (i < data->col_len)
	{
		j = 0;
		while (j < data->row_len)
		{
			x = data->points[i][j].x;
			data->points[i][j].x = (int)(x - data->points[i][j].y) * cos(0.523599);
			data->points[i][j].y = (int)(x + data->points[i][j].y) * sin(0.523599) - data->points[i][j].z;
			j++;
		}
		i++;
	}
}

void	apply_zoom(t_data *data, int zoom) {
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < data->col_len)
	{
		j = 0;
		while (j < data->row_len)
		{
			data->points[i][j].x *= zoom;
			data->points[i][j].y *= zoom;
			//data->points[i][j].z *= zoom;
			j++;
		}
		i++;
	}
}

void	put_vertical_line(mlx_image_t *img, int x1, int y1, int sum_y)
{
	int i;

	i = 0;
	ft_printf("vertical line\n");
	while (i < sum_y)
	{
		mlx_put_pixel(img, x1, y1, 0xFF0000FF);
		i++;
		y1++;
	}
}

void	put_line(mlx_image_t *img, int x1, int y1, int x2, int y2) {
	int i;
	int sum_x;
	int sum_y;
	int y;
	int x;
	int p;

	i = 0;
	sum_x = x2 - x1;
	sum_y = y2 - y1;
	p = (2 * abs(sum_y)) - sum_x;
	//printf("p: %d\n", p);
	//printf("(x1, y1) - (x2, y2) -> (%d, %d) - (%d, %d)\n", x1, y1, x2, y2);
	if (x1 == x2)
	{
		ft_printf("vertical line\n");
		while (i < abs(sum_y))
		{
			mlx_put_pixel(img, x1, y1, 0xFF0000FF);
			i++;
			y1++;
		}
		//put_vertical_line(img, x1, y1, abs(sum_y));
	}
	if (y2 < y1)
	{
		ft_printf("y2 < y1\n");
		//p -1
		if (abs(sum_x) > abs(sum_y))
		{
			ft_printf("sum_x > sum_y\n");
			y = y1;	
			while (i < abs(sum_x))
			{
				mlx_put_pixel(img, x1, y, 0xFF0000FF);
				if (p >= 0)
				{
					y--;
					p = p + (2 * abs(sum_y)) - (2 * abs(sum_x)); 
				}
				else
				{
					p = p + (2 * abs(sum_y));
				}
				i++;
				if (x1 > x2)
					x1--;
				else
					x1++;
			}
		}
		else
		{
			ft_printf("sum_x > sum_y\n");
			x = x1;
			while (i < abs(sum_y))
			{
				mlx_put_pixel(img, x, y1, 0xFF0000FF);
				if (p >= 0)
				{
					x--;
					p = p + (2 * abs(sum_x)) - (2 * abs(sum_y));

				}
				else
				{
					p = p + (2 * abs(sum_x));
				}
				i++;
				y1++;
			}

		}
	}
	else if (y2 > y1)
	{
		ft_printf("y2 > y1\n");
		if (abs(sum_x) > abs(sum_y))
		{
			ft_printf("sum_x > sum_y\n");
			y = y1;	
			while (i < abs(sum_x))
			{
				//printf("putting line\n");
				mlx_put_pixel(img, x1, y, 0xFF0000FF);
				if (p >= 0)
				{
					y++;
					p = p + (2 * abs(sum_y)) - (2 * abs(sum_x)); 
				}
				else
				{
					p = p + (2 * abs(sum_y));
				}
				i++;
				if (x1 > x2)
					x1--;
				else
					x1++;
			}
		}
		else
		{
			ft_printf("sum_x > sum_y\n");
			x = x1;
			while (i < abs(sum_y))
			{
				mlx_put_pixel(img, x, y1, 0xFF0000FF);
				if (p >= 0)
				{
					if (x1 > x2)
						x--;
					else
						x++;
					p = p + (2 * abs(sum_x)) - (2 * abs(sum_y));

				}
				else
				{
					p = p + (2 * abs(sum_x));
				}
				i++;
				y1++;
			}
		}
	}
	else if (y2 == y1)
	{
		//horiztonal line
		while (i < abs(sum_x))
		{
			mlx_put_pixel(img, x1, y1, 0xFF0000FF);
			i++;
			x1++;
		}
	}	

}

void	draw_lines(mlx_image_t *img, t_data *data, t_point **points)
{
 	int i;
	int j;

	i = 0;
	j = 0;
	/*
	if(data.col_len){};
	//put_line(img, x1, y1, x2, y2)
	//horizontal
	put_line(img, 0, 50, 100, 50);
	//vertcial
	put_line(img, 100, 0, 100, 300);	 
	//dx > dy negative slope
	put_line(img, 100, 200, 300, 15);
	//dy > dx negative slope
	put_line(img, 100, 200, 150, 5);
	//dx > dy positive slope
	put_line(img, 200, 5, 400, 50);
	//dy > dx positive slope
	put_line(img, 150, 15, 200, 150); 
	//x1 > x2
	put_line(img, 20, 20, 5, 30);
	*/

	while (i < data->col_len)
	{
		j = 0;
		while (j < data->row_len)
		{
			if (j + 1 != data->row_len)
				put_line(img, points[i][j].x, points[i][j].y, points[i][j + 1].x, points[i][j + 1].y);
			if (i + 1 != data->col_len)
				put_line(img, points[i][j].x, points[i][j].y, points[i + 1][j].x, points[i + 1][j].y);
			printf("exited put_line\n");
			j++;
		}
		i++;
	}
}

void	set_original_point_values(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < data->col_len)
	{
		x = 0;
		while (x < data->row_len)
		{
			data->points[y][x].x = data->converted_points[y][x].x;
			data->points[y][x].y = data->converted_points[y][x].y;
			data->points[y][x].z = data->converted_points[y][x].z;
			x++;
		}
		y++;
	}
}


void	zoom_image(t_data *data, int zoom)
{
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * 4);
	data->zoom += zoom;
	set_original_point_values(data);
	printf("values set\n");
	print_points(data, 1);
	printf("\n----- Original ------\n");
	print_points(data, 0);
	apply_zoom(data, data->zoom);
	apply_isometric(data);
	apply_center(data);
	printf("\n------ After Conversion ------\n");
	print_points(data, 0);
	draw_lines(data->img, data, data->points);
}

void	remove_isometric(t_data *data)
{
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * 4);
	set_original_point_values(data);
	apply_zoom(data, 15);
	apply_center(data);
	draw_lines(data->img, data, data->points);
}


void	add_z(t_data *data, int val)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < data->col_len)
	{
		x = 0;
		while (x < data->row_len)
		{
			if (data->converted_points[y][x].z != 0)
			{
				data->converted_points[y][x].z += val;
				printf("z-value: %d\n", data->converted_points[y][x].z);
			}
			x++;
		}
		y++;
	}
}

void	increment_z(t_data *data, int val)
{
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * 4);
	add_z(data, val);
	set_original_point_values(data);
	apply_zoom(data, data->zoom);
	apply_isometric(data);
	apply_center(data);
	draw_lines(data->img, data, data->points);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_data *data = param;

	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		data->img->instances[0].x += 5;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT)
		data->img->instances[0].x += 5;
	
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		data->img->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT)
		data->img->instances[0].x -= 5;
	
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		data->img->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_REPEAT)
		data->img->instances[0].y -= 5;

	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		data->img->instances[0].y += 5;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_REPEAT)
		data->img->instances[0].y += 5;

	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
		zoom_image(data, -5);
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
		zoom_image(data, 5);
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_PRESS)
		increment_z(data, 5);
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		increment_z(data, -5);
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
		remove_isometric(data);
}

int		draw_points(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!data->mlx)
	{		
		printf("error\n");
		fprintf(stderr, "%s", mlx_strerror(mlx_errno));
    		return EXIT_FAILURE;
	}

	data->img = mlx_new_image(data->mlx, 3000, 3000);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
	{
		mlx_close_window(data->mlx);
		fprintf(stderr, "%s", mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}
	
	mlx_key_hook(data->mlx, &my_keyhook, data);
	draw_lines(data->img, data, data->points);
	mlx_loop(data->mlx);
	return (0);
}

void	run_fdf(char *file_path, t_data data)
{
	int fd;
	char *str;
	int i;

	i = 0;
	fd = open(file_path, O_RDONLY, S_IRUSR);
	printf("blah\n");
	data.points = (t_point **)malloc(sizeof(t_point *) * data.col_len);
	data.converted_points = (t_point **)malloc(sizeof(t_point *) * data.col_len);
	printf("col_len: %d - row_len: %d\n", data.col_len, data.row_len);
	if (fd == -1)
		ft_printf("error opneing file\n");
	else
	{
		while (get_next_line(fd, &str))
		{
			printf("reading data\n");
			data.points[i] = (t_point *)malloc(sizeof(t_point) * data.row_len);
			data.converted_points[i] = (t_point *)malloc(sizeof(t_point) * data.row_len);
			printf("point malloced\n");
			create_tpoints(str, &data, i);
			printf("created point\n");
			i++;
			free(str);
		}
	}
	print_points(&data, 1);
	data.zoom = 15;
	apply_zoom(&data, data.zoom);
	apply_isometric(&data);
	apply_center(&data);
	print_points(&data, 0);
	draw_points(&data);
	//free(data.points);
}

void	init_data(t_data *data)
{
	data->points = NULL;
	data->converted_points = NULL;
	data->row_len = 0;
	data->col_len = 0;
	data->mlx = NULL;
	data->img = NULL;
}

int main(int argc, char **argv) 
{
	t_data data;
	int res;

	res = 0;
	init_data(&data);	
	if (argc == 1)
	{
		ft_printf("no map passed\n");
		return (1);
	}
	else if (argc >= 3)
	{
		ft_printf("Invalid formatting\n");
		return (1);
	}
	else
	{
		res = verify_file(argv[1], &data);
		printf("verified file\n");
		if (res != -1 && res)
		{
			ft_printf("file verifed\n");
			run_fdf(argv[1], data);
		}
	}

	return (0);
}
