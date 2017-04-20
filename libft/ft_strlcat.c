/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 22:34:55 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/09 23:01:16 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*dst2;
	const char	*src2;
	size_t		nb;
	size_t		len;

	dst2 = dst;
	src2 = src;
	nb = size;
	while (nb-- != 0 && *dst2 != '\0')
		dst2++;
	len = dst2 - dst;
	nb = size - len;
	if (nb == 0)
		return (len + ft_strlen(src));
	while (*src2 != '\0')
	{
		if (nb != 1)
		{
			*dst2++ = *src2;
			nb--;
		}
		src2++;
	}
	*dst2++ = '\0';
	return (len + ft_strlen(src));
}
