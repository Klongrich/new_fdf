#include "fdf.h"

void	read_file(char *file_path)
{
	int fd;
	int rd;
	
	fd = open(file_path, O_RDONLY, S_IRUSR);
	if (fd == -1)
		printf("error opening file\n");
	else
	{
		printf("reading file_path: %s\n", file_path);
	}
}

int main(int argc, char **argv) 
{
	if (argc == 1)
	{
		printf("no map passed\n");
		return (1);
	}
	else if (argc >= 3)
	{
		printf("Invalid formatting\n");
		return (1);
	}
	else
	{
		read_file(argv[1]);
		printf("valid formatting\n");		
	}

	return (0);
}
