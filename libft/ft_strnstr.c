/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 09:05:28 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/15 18:33:32 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		x;

	x = 0;
	if (*little == 0)
		return ((char *)big);
	while (len > 0 && *big != '\0')
	{
		if (*big == little[x])
			x++;
		else
		{
			while (--x > 0 && len++ && big--)
				;
			x = 0;
		}
		if (little[x] == '\0')
		{
			while (--x > 0 && big--)
				;
			return ((char *)big);
		}
		len--;
		big++;
	}
	return (NULL);
}
