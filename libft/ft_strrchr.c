/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:23:59 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/09 17:24:02 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	ch;

	len = 0;
	ch = c;
	while (*s)
	{
		s++;
		len++;
	}
	while (len > 0 && *s != ch)
	{
		len--;
		s--;
	}
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}
