#include "fdf.h"

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
