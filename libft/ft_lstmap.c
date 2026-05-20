/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 17:51:07 by klongric          #+#    #+#             */
/*   Updated: 2017/01/10 18:34:18 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*list;
	t_list	*temp;

	list = f(lst);
	temp = list;
	if (!list)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		temp->next = f(lst);
		temp = temp->next;
	}
	return (list);
}
