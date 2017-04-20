/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoau.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:58:53 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:49:18 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char		*ft_itoau(size_t n)
{
	int		len;
	size_t	temp;
	char	*str;

	len = 2;
	temp = n;
	while (temp /= 10)
		len++;
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
	return (str);
}
