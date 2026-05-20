/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:39:33 by klongric          #+#    #+#             */
/*   Updated: 2017/01/10 01:46:02 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *big, const char *little)
{
	const char	*x1;
	const char	*x2;

	if (!*little)
		return ((char *)big);
	while (*big)
	{
		if (*big == *little)
		{
			x1 = big + 1;
			x2 = little + 1;
			while (*x1 && *x2 && *x1 == *x2)
			{
				++x1;
				++x2;
			}
			if (!*x2)
				return ((char *)big);
		}
		big++;
	}
	return (0);
}
