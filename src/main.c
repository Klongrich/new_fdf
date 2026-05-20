#include "fdf.h"

void	read_file(char *file_path)
{
	int fd;
	char *str;

	fd = open(file_path, O_RDONLY, S_IRUSR);
	if (fd == -1)
		ft_printf("error opening file\n");
	else
	{
		while(get_next_line(fd, &str))
		{
			ft_printf("str: %s\n", str); 
		}
	}
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
		read_file(argv[1]);
		ft_printf("valid formatting\n");		
	}

	return (0);
}
