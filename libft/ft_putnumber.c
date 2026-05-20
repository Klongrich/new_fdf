
#include "libft.h"

int     ft_putnumber(long long n, int base) {
	int     count;
	char    *symbols;
 
	count = 0;
	symbols = "0123456789abcdef";
	if (n == 0)
		return (ft_putchar('0'));
	else if (n < 0) {
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= base)
		count += ft_putnumber(n / base, base);
	count += ft_putchar(symbols[n % base]);
	return (count);
}
