#include "libft.h"

int		ft_numlen_ull(unsigned long long n)
{
	unsigned long long  i;

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
		n /= 10;
		i++;
	}
	return (i);
}
