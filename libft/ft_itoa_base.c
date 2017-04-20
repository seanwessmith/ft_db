/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 09:02:26 by exam              #+#    #+#             */
/*   Updated: 2017/03/24 14:47:56 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_itoa_base(int value, int base)
{
	int		len;
	int		neg;
	int		v;
	char	*str;

	if (base < 2 || base > 16)
		return (0);
	neg = (base == 10 && value < 0) ? 1 : 0;
	len = 1 + neg;
	v = value;
	while (v /= base)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[0] = '-';
	str[len] = 0;
	while (len-- > neg)
	{
		v = (value < 0) ? -(value % base) : (value % base);
		str[len] = (v > 9) ? v + 'A' - 10 : v + '0';
		value /= base;
	}
	return (str);
}
