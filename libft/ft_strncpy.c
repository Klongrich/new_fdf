/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 11:10:26 by klongric          #+#    #+#             */
/*   Updated: 2017/01/14 13:46:55 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*dup;
	size_t	start;

	dup = dst;
	start = len;
	if (!len)
		return (dup);
	while (*src && len--)
		*dst++ = *src++;
	if (len <= start)
		ft_bzero(dst, len);
	return (dup);
}
