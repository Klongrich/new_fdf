/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 21:18:30 by klongric          #+#    #+#             */
/*   Updated: 2017/01/14 13:33:39 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (!s)
		return (0);
	i = 0;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	while (start--)
		s++;
	while (len--)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}
