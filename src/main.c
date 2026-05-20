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


int		verify_file(char *file_path)
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
			free(str);
			i++;
		}
	}
	close(fd);
	return (1);
}

int main(int argc, char **argv) 
{
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
		verify_file(argv[1]);
	}

	return (0);
}
