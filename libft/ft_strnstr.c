/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 01:39:18 by klongric          #+#    #+#             */
/*   Updated: 2017/01/11 22:40:51 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char		*x1;
	const char		*x2;
	size_t			n;

	if (!*little)
		return ((char *)big);
	while (len-- && *big)
	{
		if (*big == *little)
		{
			n = len;
			x1 = big + 1;
			x2 = little + 1;
			while (*x1 == *x2 && *x1 && *x2 && n--)
			{
				x1++;
				x2++;
			}
			if (!*x2)
				return ((char *)big);
		}
		big++;
	}
	return (0);
}
