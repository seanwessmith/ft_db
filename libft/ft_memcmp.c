/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 13:49:29 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/09 20:10:03 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char str1;
	unsigned char str2;

	while (n--)
	{
		str1 = *(unsigned char *)s1;
		str2 = *(unsigned char *)s2;
		if (str1 != str2)
		{
			return (str1 - str2);
		}
		s1++;
		s2++;
	}
	return (0);
}
