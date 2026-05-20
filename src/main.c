#include "fdf.h"

int		contains_number(char *str) {
	int i;

	i = 0;
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
			if (i == 0)
				row_len = get_rowlen(str);
			if (row_len != get_rowlen(str))
			{
				close(fd);
				free(str);
				return(print_error(get_rowlen(str)));
			}
			i++;
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
		i++;
	}
}

void	print_points(t_data data) {
	int i;
	int y;

	i = 0;
	y = 0;
	while (i < data.col_len)
	{
		y = 0;
		while (y < data.row_len)
		{
			ft_printf("(x, y, z) -> (%d, %d, %d)\n", data.points[i][y].x, data.points[i][y].y, data.points[i][y].z);
			y++;
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
			data->points[i][j].z *= zoom;
			j++;
		}
		i++;
	}
}


void	draw_lines(mlx_image_t *img, t_data data)
{
 	int i;

	i = 0;
	while (i < data.row_len)
	{
		mlx_put_pixel(img, i, 10, 0xFF0000FF);
		i++;
	}
}

int		draw_points(t_data data)
{

	mlx_t *mlx;
	mlx_image_t *img;

	mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!mlx)
	{		
		printf("error\n");
		fprintf(stderr, "%s", mlx_strerror(mlx_errno));
    		return EXIT_FAILURE;
	}

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	{
		mlx_close_window(mlx);
		fprintf(stderr, "%s", mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}

	draw_lines(img, data);
	mlx_loop(mlx);
	return (0);
}


void	run_fdf(char *file_path, t_data data)
{
	int fd;
	char *str;
	int i;

	i = 0;
	fd = open(file_path, O_RDONLY, S_IRUSR);
	data.points = (t_point **)malloc(sizeof(t_point *) * data.col_len);
	if (fd == -1)
		ft_printf("error opneing file\n");
	else
	{
		while (get_next_line(fd, &str))
		{
			data.points[i] = (t_point *)malloc(sizeof(t_point) * data.row_len);
			create_tpoints(str, &data, i);
			i++;
			free(str);
		}
	}
	apply_zoom(&data, 15);
	print_points(data);
	draw_points(data);
	//create free t_points function
	free(data.points);
}

void	init_data(t_data *data)
{
	data->points = NULL;
	data->row_len = 0;
	data->col_len = 0;
}

int main(int argc, char **argv) 
{
	t_data data;

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
		if (verify_file(argv[1], &data))
		{
			ft_printf("file verifed\n");
			run_fdf(argv[1], data);
		}
	}

	return (0);
}
