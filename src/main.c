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

void	run_fdf(char *file_path, t_data data) {
	int fd;
	char *str;

	fd = open(file_path, O_RDONLY, S_IRUSR);
	ft_printf("col_len: %d - row_len: %d\n", data.col_len, data.row_len);
	data.points = (t_point **)malloc(sizeof(t_point *) * data.col_len);
	if (fd == -1)
		ft_printf("error opneing file\n");
	else
	{
		while (get_next_line(fd, &str))
		{
			ft_printf("str: %s\n", str);
			free(str);
		}
	}
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
