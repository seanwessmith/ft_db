/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 12:07:28 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/09 16:35:11 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	i = 0;
	if (!len)
		return (dst);
	if (dst < src)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
		return (dst);
	}
	s += len - 1;
	d += len - 1;
	while (len--)
		*d-- = *s--;
	return (dst);
}
