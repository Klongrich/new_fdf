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

int		init_frame(t_data *data)
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
	data.points = (t_point **)malloc(sizeof(t_point *) * data.col_len);
	data.converted_points = (t_point **)malloc(sizeof(t_point *) * data.col_len);
	if (fd == -1)
		ft_printf("error opneing file\n");
	else
	{
		while (get_next_line(fd, &str))
		{
			data.points[i] = (t_point *)malloc(sizeof(t_point) * data.row_len);
			data.converted_points[i] = (t_point *)malloc(sizeof(t_point) * data.row_len);
			create_tpoints(str, &data, i);
			i++;
			free(str);
		}
	}
	data.zoom = 15;
	apply_zoom(&data, data.zoom);
	apply_isometric(&data);
	apply_center(&data);
	init_frame(&data);
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
		if (res != -1 && res)
			run_fdf(argv[1], data);
	}

	return (0);
}
