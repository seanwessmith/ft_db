/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:24:37 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 15:19:27 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcstr(const char *s, int c, int c2)
{
	int		i;
	char	*ret;
	char	ch;
	char	ch2;

	i = 0;
	if (!s)
		return (NULL);
	ch = c;
	ch2 = c2;
	while (s[i] && s[i] != ch && s[i] != ch2)
		i++;
	ret = (char *)ft_memalloc(sizeof(char) * i);
	i = 0;
	while (s[i] && s[i] != ch && s[i] != ch2)
	{
		ret[i] = s[i];
		i++;
	}
	if (s[i] == ch || s[i] == ch2)
		return ((char *)ret);
	return (NULL);
}
