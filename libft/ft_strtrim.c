/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 21:47:02 by klongric          #+#    #+#             */
/*   Updated: 2017/01/14 13:35:41 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		flags(const char *s)
{
	while (*s == ' ' || *s == '\n' || *s == '\t')
	{
		s++;
		if (!*s)
			return (1);
	}
	return (0);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	int		i;

	if (!s)
		return (0);
	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (0);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	while (*s)
	{
		if (flags(&*s))
			break ;
		str[i++] = *s++;
	}
	str[i] = '\0';
	return (str);
}
