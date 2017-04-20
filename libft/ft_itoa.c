/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:16:00 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/15 18:41:34 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_sign(int *n, int *sign, int *temp, int *len)
{
	if (*n < 0)
	{
		*sign = 1;
		*n *= -1;
	}
	while (*temp /= 10)
		(*len)++;
	*len += *sign;
}

char		*ft_itoa(int n)
{
	int		sign;
	int		len;
	int		temp;
	char	*str;

	len = 2;
	sign = 0;
	temp = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ft_sign(&n, &sign, &temp, &len);
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	len--;
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
