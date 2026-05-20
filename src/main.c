#include "fdf.h"

int main(int argc, char **argv) {
	int rd;
	int fd;

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
		printf("valid formatting\n");		
	}

	return (0);
}
