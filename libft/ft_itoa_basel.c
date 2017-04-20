/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_basel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 21:28:01 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:47:10 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_itoa_basel(unsigned long long value, long base)
{
	long				len;
	long				neg;
	unsigned long long	v;
	char				*str;

	if (base < 2 || base > 16)
		return (0);
	neg = 0;
	len = 1 + neg;
	v = value;
	while (v /= base)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[0] = '-';
	str[len] = 0;
	while (len-- > neg)
	{
		v = value % base;
		if (v > 9)
			str[len] = v + 'A' - 10;
		else
			str[len] = v + '0';
		value /= base;
	}
	return (str);
}
