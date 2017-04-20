/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 15:36:01 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:45:30 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void	ft_sign(long long *n, short *sign, long long *temp, int *len)
{
	if (*n < 0)
	{
		*sign = 1;
		*n *= -1;
	}
	while (*temp /= 10)
		(*len)++;
	*len += (int)*sign;
}

char		*ft_itoal(long long n)
{
	short		sign;
	int			len;
	long long	temp;
	char		*str;

	len = 2;
	sign = 0;
	temp = n;
	if (n < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	if (n > 9223372036854775806)
		return (ft_strdup("9223372036854775807"));
	ft_sign(&n, &sign, &temp, &len);
	str = (char *)malloc(sizeof(char) * len--);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
