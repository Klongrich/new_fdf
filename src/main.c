#include "fdf.h"

void	read_file(char *file_path)
{
	int fd;
	//int rd;
	
	fd = open(file_path, O_RDONLY, S_IRUSR);
	if (fd == -1)
		ft_printf("error opening file\n");
	else
	{
		ft_printf("reading file_path: %s\n", file_path);
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
