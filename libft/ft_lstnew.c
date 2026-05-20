/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 16:23:21 by klongric          #+#    #+#             */
/*   Updated: 2017/01/14 15:36:58 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlist;
	void	*stuff;

	stuff = (void *)content;
	newlist = (t_list *)malloc(sizeof(t_list) * content_size);
	if (!newlist)
		return (0);
	newlist->content = ft_memalloc(content_size);
	if (!content)
	{
		newlist->content = 0;
		content_size = 0;
	}
	else
		newlist->content = ft_memcpy(newlist->content, stuff, content_size);
	newlist->content_size = content_size;
	newlist->next = 0;
	return (newlist);
}
