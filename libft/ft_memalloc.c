/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:42:46 by klongric          #+#    #+#             */
/*   Updated: 2017/01/10 22:52:12 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*block;

	block = (void *)malloc(sizeof(void) * size);
	if (!block)
		return (0);
	ft_bzero(&*block, size);
	return (block);
}
