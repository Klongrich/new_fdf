/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 22:27:34 by klongric          #+#    #+#             */
/*   Updated: 2017/01/10 15:50:44 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_f(int n)
{
	long num;
	int count;

	count = 0;
	num = (long)n;
	if (num < 0)
		num *= -1;
	if (num > 9)
		count += ft_putnbr_f(num / 10);
	count += ft_putchar((num % 10) + 48);
	return (count);
}
