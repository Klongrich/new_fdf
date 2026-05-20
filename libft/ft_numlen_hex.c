#include "libft.h"

int		ft_numlen_hex(long n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	if (n == 0)
		i++;
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}
