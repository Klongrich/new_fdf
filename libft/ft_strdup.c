/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 10:11:37 by klongric          #+#    #+#             */
/*   Updated: 2017/01/09 21:47:05 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!dup)
		return (0);
	ft_strcpy(dup, s1);
	return (dup);
}
