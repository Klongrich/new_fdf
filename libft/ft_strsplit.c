/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klongric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 18:22:51 by klongric          #+#    #+#             */
/*   Updated: 2017/01/20 21:52:12 by klongric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		wordcount(const char *s, char c)
{
	int count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static	int		lettercount(const char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static	char	*createword(const char *str, char c)
{
	char	*temp;
	int		i;

	i = 0;
	temp = (char *)malloc(sizeof(char) * lettercount(str, c) + 1);
	if (!temp)
		return (0);
	while (str[i] != c && str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char			**ft_strsplit(char const *s, char c)
{
	const char		**array;
	int				x;
	int				count;

	if (!s)
		return (0);
	count = wordcount(s, c);
	array = (const char **)malloc(sizeof(const char *) * count + 1);
	x = 0;
	if (!array)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		array[x++] = (const char *)createword(&*s, c);
		while (*s && *s != c)
			s++;
		if (count == 1)
			break ;
	}
	array[x] = NULL;
	return ((char **)array);
}
