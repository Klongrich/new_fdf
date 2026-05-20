/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:47:53 by klongric          #+#    #+#             */
/*   Updated: 2017/01/23 17:11:32 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int	len(long n)
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
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	num;

	num = (long)n;
	str = (char *)malloc(sizeof(char) * len(n) + 1);
	if (!str)
		return (0);
	i = len(n);
	if (num < 0)
	{
		num *= -1;
		str[0] = '-';
	}
	if (num == 0)
		str[0] = '0';
	i--;
	while (num)
	{
		str[i--] = (num % 10) + '0';
		num /= 10;
	}
	str[len(n)] = '\0';
	return (str);
}
