#include "fdf.h"

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

void	apply_isometric(t_data *data)
{
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

void	apply_zoom(t_data *data, int zoom)
{
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
			data->points[i][j].z *= (zoom * 0.1);
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

void    render_data(t_data *data)
{
	apply_zoom(data, data->zoom);
	apply_isometric(data);
	apply_center(data);
	draw_lines(data->img, data, data->points);
}

void	zoom_image(t_data *data, int zoom)
{
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * 4);
	data->zoom += zoom;
	set_original_point_values(data);

	render_data(data);
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
			if (data->converted_points[y][x].has_z_value && data->converted_points[y][x].z < 100)
				data->converted_points[y][x].z += val;
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

	render_data(data);
}
