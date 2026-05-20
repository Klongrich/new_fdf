/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 11:34:00 by klongric          #+#    #+#             */
/*   Updated: 2017/01/18 23:41:50 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int i;
	int count;

	i = 0;
	count = ft_strlen(s2);
	while (s1[i])
		i++;
	while (count--)
		s1[i++] = *s2++;
	s1[i] = '\0';
	return (s1);
}
