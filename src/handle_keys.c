#include "fdf.h"

void	handle_arrow_keys(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->img->instances[0].x += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->img->instances[0].x -= 5;	
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->img->instances[0].y -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->img->instances[0].y += 5;
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_data *data = param;

	handle_arrow_keys(data);
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
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		data->rotation += 1;
		apply_rotation(data, data->rotation);
	}
}
