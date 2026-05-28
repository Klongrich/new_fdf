#include "fdf.h"

void	put_line(mlx_image_t *img, int x1, int y1, int x2, int y2)
{
	int	dx = abs(x2 - x1);
	int	dy = abs(y2 - y1);
	int	sx = (x1 < x2) ? 1 : -1;
	int	sy = (y1 < y2) ? 1 : -1;
	int	err = dx - dy;
	int	e2;

	while (1)
	{
		mlx_put_pixel(img, x1, y1, 0xFF0000FF);
		if (x1 == x2 && y1 == y2)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	draw_lines(mlx_image_t *img, t_data *data, t_point **points)
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
			if (j + 1 != data->row_len)
				put_line(img, points[i][j].x, points[i][j].y, points[i][j + 1].x, points[i][j + 1].y);
			if (i + 1 != data->col_len)
				put_line(img, points[i][j].x, points[i][j].y, points[i + 1][j].x, points[i + 1][j].y);
			j++;
		}
		i++;
	}
}
