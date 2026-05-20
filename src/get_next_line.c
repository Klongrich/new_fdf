/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 22:38:10 by klongric          #+#    #+#             */
/*   Updated: 2017/02/28 00:39:05 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	ret = dst;
	while (n--)
		*(unsigned char *)dst++ = *(unsigned char*)src++;
	return (ret);
}

int		checkend(char **list, int i)
{
	if (i != 0)
	{
		(*list)[i] = '\0';
		return (1);
	}
	return (0);
}

void	swap(char **list, int i, char *temp)
{
	temp = *list;
	*list = (char *)malloc(sizeof(char) * i + 1);
	ft_memcpy(*list, temp, i);
	free(temp);
}

int		get_next_line(const int fd, char **list)
{
	char			buf[BUFF_SIZE];
	char			*temp;
	static int		i;

	i = 0;
	temp = 0;
	if (!list || read(fd, buf, 0) < 0)
		return (-1);
	if (!(*list = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	while ((read(fd, buf, 1) > 0))
	{
		if (buf[0] == '\n')
		{
			(*list)[i] = '\0';
			return (1);
		}
		swap(list, i, temp);
		(*list)[i] = buf[0];
		i++;
	}
	return (checkend(list, i));
}
