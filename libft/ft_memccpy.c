/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 11:10:49 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/10 16:56:41 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*d;
	unsigned const char		*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	c = (unsigned char)c;
	while (n--)
	{
		*d = *s;
		d++;
		if (*s == c)
			return (d);
		s++;
	}
	return (NULL);
}
